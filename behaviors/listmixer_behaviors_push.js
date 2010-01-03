// $Id$

Drupal.behaviors.listmixer.Push = function() {
  this.init = function() {
   // alert('Push Library Loaded');
  }

  /* Library Functions */  
  this.textPush = function() {
    alert('push text');
  }
  
  this.nodereferencePush = function() {
    alert('push nodereference');
  }
  this.linkPush = function() {
    alert('push link');
  }
  this.filefieldPush = function() {
    alert('push filefield');
  }
  this.termPush = function() {
    alert('push term');
  }
}



