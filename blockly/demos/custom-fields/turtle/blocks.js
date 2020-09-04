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
 * @fileoverview Turtle field demo blocks..
 * @author bekawestberg@gmail.com (Beka Westberg)
 */

Blockly.Blocks['turtle_basic'] = {
  init: function() {
    this.appendDummyInput()
        .appendField('simple turtle');
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_CENTRE)
        .appendField(new CustomFields.FieldTurtle(), 'TURTLE');
    this.setStyle('loop_blocks');
    this.setCommentText('Demonstrates a turtle field with no validator.');
  }
};

Blockly.Blocks['turtle_nullifier'] = {
  init: function() {
    this.appendDummyInput()
        .appendField('no trademarks');
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_CENTRE)
        .appendField(new CustomFields.FieldTurtle(null, null, null, this.validate)
            , 'TURTLE');
    this.setStyle('loop_blocks');
    this.setCommentText('Validates combinations of names and hats to null' +
      ' (invalid) if they could be considered infringe-y. This turns the' +
      ' turtle field red. Infringe-y combinations are: (Leonardo, Mask),' +
      ' (Yertle, Crown), and (Franklin, Propeller).');
  },

  validate: function(newValue) {
    this.cachedValidatedValue_ = {
      turtleName: newValue.turtleName,
      pattern: newValue.pattern,
      hat: newValue.hat,
    };
    if ((newValue.turtleName == 'Leonardo' && newValue.hat == 'Mask') ||
        (newValue.turtleName == 'Yertle' && newValue.hat == 'Crown') ||
        (newValue.turtleName == 'Franklin') && newValue.hat == 'Propeller') {

      var currentValue = this.getValue();
      if (newValue.turtleName != currentValue.turtleName) {
        // Turtle name changed.
        this.cachedValidatedValue_.turtleName = null;
      } else {
        // Hat must have changed.
        this.cachedValidatedValue_.hat = null;
      }

      return null;
    }
    return newValue;
  }
};

Blockly.Blocks['turtle_changer'] = {
  init: function() {
    this.appendDummyInput()
      .setAlign(Blockly.ALIGN_CENTRE)
        .appendField('force hats');
    this.appendDummyInput()
        .appendField(new CustomFields.FieldTurtle(
            'Dots', 'Crown', 'Yertle',  this.validate), 'TURTLE');
    this.setStyle('loop_blocks');
    this.setCommentText('Validates the input so that certain names always' +
      ' have specific hats. The name-hat combinations are: (Leonardo, Mask),' +
      ' (Yertle, Crown), (Franklin, Propeller).');
  },

  validate: function(newValue) {
    switch(newValue.turtleName) {
      case 'Leonardo':
        newValue.hat = 'Mask';
        break;
      case 'Yertle':
        newValue.hat = 'Crown';
        break;
      case 'Franklin':
        newValue.hat = 'Propeller';
        break;
    }
    return newValue;
  }
};
