// $Id$

Drupal.behaviors.listmixer.submitBehavior = function(preset) {
  this.init = function() {
  }
  this.buttonSubmit = function(preset) {  
    $('div.' + preset.interactiveElementContainerId + '-push-submit').children('.button').click(function() {
      Drupal.behaviors.listmixer.executePush(preset);
    });
  }
  this.buttonSubmitRefresh = function(preset) {  
    $('div.' + preset.interactiveElementContainerId + '-push-submit').children('.button').click(function() {
      Drupal.behaviors.listmixer.executePush(preset);
    });
    $('div.' + preset.interactiveElementContainerId + '-push-refresh').children('.button').click(function() {
      Drupal.behaviors.listmixer.reloadPage();
    });
  }
  this.markup = function(preset) {
    return { 
      buttonSubmit : '<div class="' + preset.interactiveElementContainerId + '-push-submit listmixer-push-submit"><button class="button">Save</button></div>',
      buttonSubmitRefresh : '<div class="' + preset.interactiveElementContainerId + '-push-submit listmixer-push-submit"><button class="button">Save</button></div><div class="' + preset.interactiveElementContainerId + '-push-refresh listmixer-push-refresh"><button class="button">Refresh</button></div>'
    }
  };
}
