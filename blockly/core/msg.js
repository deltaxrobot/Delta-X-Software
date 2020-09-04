/**
 * @license
 * Copyright 2013 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @fileoverview Empty name space for the Message singleton.
 * @author scr@google.com (Sheridan Rawlins)
 */
'use strict';

/**
 * Name space for the Msg singleton.
 * Msg gets populated in the message files.
 */
goog.provide('Blockly.Msg');

goog.require('Blockly.utils.global');


/**
 * Exported so that if Blockly is compiled with ADVANCED_COMPILATION,
 * the Blockly.Msg object exists for message files included in script tags.
 */
if (!Blockly.utils.global['Blockly']) {
  Blockly.utils.global['Blockly'] = {};
}
if (!Blockly.utils.global['Blockly']['Msg']) {
  Blockly.utils.global['Blockly']['Msg'] = Blockly.Msg;
}
