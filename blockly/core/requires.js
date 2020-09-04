/**
 * @license
 * Copyright 2019 Google LLC
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
 * @fileoverview Default Blockly entry point. Use this to pick and choose which
 * fields and renderers to include in your Blockly bundle.
 * @author samelh@google.com (Sam El-Husseini)
 */
'use strict';

goog.provide('Blockly.requires');

// Blockly Core (absolutely mandatory).
goog.require('Blockly');


// If block comments aren't required, then Blockly.inject's "comments"
// configuration must be false, and no blocks may be loaded from XML which
// define comments.
goog.require('Blockly.Comment');
// One of these two will almost certainly be needed (usually VerticalFlyout).
goog.require('Blockly.HorizontalFlyout');
goog.require('Blockly.VerticalFlyout');
// Flyout buttons are needed by the variable category,
// and by any custom toolbox that has a button or a label.
goog.require('Blockly.FlyoutButton');
// If there is code generation into any language, then the generator is needed.
// Should not be required when using advanced compilation since
// individual generator files should already have this require.
goog.require('Blockly.Generator');
// If the toolbox does not have categories and only has a simple flyout, then
// 'Blockly.Toolbox' is not needed.
goog.require('Blockly.Toolbox');
// If a trashcan on the workspace isn't required, then Blockly.inject's
// "trashcan" configuration must be false.
goog.require('Blockly.Trashcan');
// Only needed if one is using the 'VARIABLE_DYNAMIC' typed variables category.
goog.require('Blockly.VariablesDynamic');
// Only need to require these two if you're using workspace comments.
// goog.require('Blockly.WorkspaceCommentSvg');
// goog.require('Blockly.WorkspaceCommentSvg.render');
// If zoom controls aren't required, then Blockly.inject's
// "zoom"/"controls" configuration must be false.
goog.require('Blockly.ZoomControls');


// Block dependencies.
// None of these should be required when using advanced compilation since
// individual block files should include the requirements they depend on.
goog.require('Blockly.Mutator');
goog.require('Blockly.Warning');
goog.require('Blockly.FieldAngle');
goog.require('Blockly.FieldCheckbox');
goog.require('Blockly.FieldColour');
goog.require('Blockly.FieldDropdown');
goog.require('Blockly.FieldLabelSerializable');
goog.require('Blockly.FieldImage');
goog.require('Blockly.FieldTextInput');
goog.require('Blockly.FieldMultilineInput');
goog.require('Blockly.FieldNumber');
goog.require('Blockly.FieldVariable');

// If you'd like to include the date field in your build, you will also need to
// include the closure library as a build dependency.  You can do so by running:
//     gulp build-compressed --closure-library
// Be sure to also include "google-closure-library" to your list of
// devDependencies.
// goog.require('Blockly.FieldDate');


// Blockly Renderers.
// At least one renderer is mandatory.  Geras is the default one.
// Others may be chosen using Blockly.inject's "renderer" configuration.
goog.require('Blockly.geras.Renderer');
goog.require('Blockly.thrasos.Renderer');
goog.require('Blockly.zelos.Renderer');
// The debug renderer, which shows simplified versions of the blocks for
// developer use.
// goog.require('Blockly.blockRendering.Debug');

// Blockly Themes.
// Classic is the default theme.
goog.require('Blockly.Themes.Classic');
goog.require('Blockly.Themes.Dark');
goog.require('Blockly.Themes.Deuteranopia');
goog.require('Blockly.Themes.HighContrast');
goog.require('Blockly.Themes.Tritanopia');
// goog.require('Blockly.Themes.Modern');
