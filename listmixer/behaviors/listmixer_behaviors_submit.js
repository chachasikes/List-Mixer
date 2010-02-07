// $Id$

Drupal.behaviors.listmixer.submitBehavior = function(preset) {
  this.init = function() {
  }

  /* Library Functions */ 
  
  this.buttonSubmit = function() {  
    if(preset.administerSettings === true) {
/*       alert(Drupal.t('submit button')); */
    }
  }
   
  this.checkboxSubmit = function() {
    if(preset.administerSettings === true) {
/*       alert(Drupal.t('submit checkbox')); */
    }
  }
  this.markup = function(preset) {
    return { 
      // @TODO checkboxSubmit not quite figured out yet.
      // checkboxSubmit : '<div class="' + preset.interactiveElementContainerId + 'push-submit"><button class="button">Save</button></div>',
      buttonSubmit : '<div class="' + preset.interactiveElementContainerId + '-push-submit listmixer-push-submit"><button class="button">Save</button></div>'
    }
  };
}
