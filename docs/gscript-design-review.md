# G-Script design review

This review follows the current interpreter and its software test fixtures. One
reviewer inspected control flow and execution boundaries independently of the
implementation changes. Findings were passed to a second developer for fixes
and regression tests. This is a focused review, not an exhaustive language audit.

## Corrections in this change

| Problem | Corrected behavior | Regression coverage |
| --- | --- | --- |
| Inline conditional handlers advanced the program counter before dispatching a statement that also advanced it. | The selected statement owns its program-counter transition; the following line executes exactly once. | Assignment, false condition, ELIF/ELSE, delay, device command, function call, and legacy subprogram call. |
| Bracket substitution evaluated a `waitUntil` condition before polling and modified quoted payloads. | Deferred conditions retain their expression; quoted strings and device command payloads remain literal. | A variable changes after the wait starts; canonical and compatibility spellings, quoted brackets, unmatched literal brackets, operators, whitespace, and compact assignments. |
| Local-only loops monopolized the worker event loop. | Execution yields after at most 64 local statements or after a batch reaches 5 ms. Continuations are tied to the current execution generation. | An endless local loop accepts queued Stop; a continuation from an old run cannot resume a restarted program during a timer wait. |
| Legacy subprogram return addresses survived Stop and a later run. | Each run starts with an empty subprogram return stack; terminal cleanup clears it too. | Stop inside a subprogram, then execute `M99` in a new run and require a fault. |
| Returning early from a function left its conditional and loop frames on the caller's stacks. | Function entry records block-stack depths; RETURN and ENDFUNCTION restore those depths. | Early return from nested FOR/WHILE/IF/SWITCH inside a caller that also owns those blocks. |

The batch interval is a cooperative scheduling limit checked between statements,
not a hard real-time bound. A single expensive statement or synchronous plugin
callback can still take longer. Firmware continues to perform motion execution.

## Follow-up hardening

The follow-up addresses the scope and parsing gaps identified during the first
review and broadens verification to the real worker-thread composition.

| Area | Implementation and verification |
| --- | --- |
| Jump scopes | The analyzer records conditional branch, loop, function, and legacy subprogram ancestry for labels and numbered targets. JUMP/GOTO across those boundaries fails preflight, including transfers inside inline IF. Same-scope jumps and legacy M98 calls remain supported. |
| Loop transfers | BREAK/CONTINUE use nesting order within the current function and discard conditional/switch frames crossed by the transfer. Caller loops remain outside the callee's control. |
| Shared syntax | `GScriptSyntax.h` supplies quote-aware comments, string masking, inline statement extraction, argument splitting, macro normalization, and immutable built-in primitive signatures/arity to analyzer, editor, and runtime. |
| Expression faults | Invalid operands, non-finite results, division/modulo by zero, incorrect function arity, and invalid numeric primitive arguments fault the run before its next device command. Undefined-name compatibility is retained for literal reads, not invalid numeric use. |
| Diagnostics | Runtime failures retain source line/text, command/device, and function/subprogram call context in project-scoped failure telemetry before cleanup. |
| Ambiguous device replies | Interrupted, timed-out, or disconnected response-bearing transactions quarantine the transport. A confirmed fresh transport session is required before ordinary work resumes; late responses and cell Reset alone do not clear ambiguity. |
| Tracking completion | Correlated tracking operations return a request ID and snapshot to the requesting worker. The worker accepts only the current wait before publishing result variables, so a stopped request cannot overwrite a restarted run's target. Semantic object ownership remains separate from request identity; Stop leaves a claim to expire under its lease. |
| Real worker threads | Integration fixtures exercise queued Stop/restart, shared project variables with project isolation, camera timer receiver affinity, and provider failures/exceptions through actual QThread workers. |
| Build identity | `python start.py` builds and opens the current checkout. App titles and CLI build information identify the compiled version and source revision. |

See the [acceptance and commissioning checklist](gscript-acceptance-checklist.md)
for the recovery procedure and physical validation record. Executed test counts
belong in the matching CI/test logs, not in a permanently fixed checklist.

## Remaining architectural boundaries

The common lexical helpers and primitive catalog are not a typed AST or a proof
that every possible expression is valid at compile time. Data-dependent errors
still require runtime validation. Further language extensions must use the common
contracts and add analyzer/runtime agreement tests.

Scheduling remains cooperative. A synchronous plugin callback can delay the
worker until it returns; an execution batch is not a preemptive deadline. Device
responses without protocol-level sequence numbers require explicit transport
recovery after ambiguity rather than automatic retry.

Shared variable access is thread-safe, but read-modify-write statements across
workers are not atomic transactions. Tracking claims, not variable assignments,
provide object ownership. Real encoder alignment, motion compensation, vacuum
feedback, and pick success still require physical commissioning.

## Verification boundary

Run the relevant software suites with the current Qt/OpenCV development kit:

```bash
python tools/run-tests.py --test gscript_runtime --test gscript_analyzer --test cli_integration --test control_plane
```

These fixtures check language execution, asynchronous dispatch, CLI composition,
and broker behavior. They do not establish physical robot response, conveyor
tracking accuracy, or live picking performance. No physical robot commands were
required for this review.
