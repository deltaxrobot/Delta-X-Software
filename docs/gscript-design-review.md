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

## Remaining design gaps

These findings come from source inspection and need dedicated regression tests
before implementation. They are not fixed by the corrections above.

### Transfers between lexical scopes

The analyzer resolves label and numbered-line targets but does not consistently
verify that a jump stays within a valid block scope. For example, a jump can
enter a FOR body without creating its loop frame:

```gcode
JUMP INNER
FOR #i = 1 TO 2
LABEL INNER
#Count = 1
ENDFOR
```

The runtime guide already prohibits scope-crossing jumps. Preflight should also
enforce that rule by recording block ancestry for each source line and target.

### BREAK and CONTINUE scope cleanup

Function-return cleanup does not address all nonlocal transfers. A CONTINUE
inside IF can leave that conditional frame behind on each iteration:

```gcode
#i = 0
WHILE #i < 100
    IF 1
        #i = #i + 1
        CONTINUE
    ENDIF
ENDWHILE
```

Loop transfers should unwind the scopes they leave and retain the caller's
outer scopes. Nested loop types and SWITCH require explicit tests for which
construct receives BREAK or CONTINUE.

### Shared statement interpretation

The analyzer, editor helpers, and interpreter separately tokenize and normalize
source text. This permits preflight/runtime disagreements and repeated command
catalogs. An incremental improvement is a shared quote-aware tokenizer and
immutable statement description, followed by shared primitive metadata. A full
language rewrite is not required to address the concrete defects above.

## Verification boundary

Run the relevant software suites with the current Qt/OpenCV development kit:

```bash
python tools/run-tests.py --test gscript_runtime --test gscript_analyzer --test cli_integration --test control_plane
```

These fixtures check language execution, asynchronous dispatch, CLI composition,
and broker behavior. They do not establish physical robot response, conveyor
tracking accuracy, or live picking performance. No physical robot commands were
required for this review.
