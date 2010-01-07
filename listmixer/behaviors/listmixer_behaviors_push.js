// $Id$

Drupal.behaviors.listmixer.Push = function() {
  this.init = function() {
   // alert('Push Library Loaded');
  }

  /* Library Functions */  
  this.textPush = function() {
    alert(Drupal.t('push text'));
  }
  
  this.nodereferencePush = function() {
    alert(Drupal.t('push nodereference'));
  }
  this.linkPush = function() {
    alert(Drupal.t('push link'));
  }
  this.filefieldPush = function() {
    alert(Drupal.t('push filefield'));
  }
  this.termPush = function() {
    alert(Drupal.t('push term'));
  }
}



