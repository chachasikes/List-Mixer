// $Id$

/**
 * Xplor Homepage defered loading.
 */

// Resize the parent lighbox when everything is loaded.

$(window).load(function() {
    var loadTimer = setTimeout(xplorLoadLightbox, 0);
});
// Set the links in this window to open up in a new window unless they are lighbox links.
$(document).ready(function() {
  $('a:not(.lightbox-processed)').click(function() {
    top.location = this.href;
    return false;
  });
});

function xplorLoadLightbox() {
  if (this.document !== top.document) {
    var w = 0, h = 0, scrolling = 'no';
    $('object, img, .xplor-printables #content-area', this.document).each(function() {
      w = Math.max(w, $(this).width());
    });
    w = w ? w : 600;
  
    // Set the width of the body so that text content can layout correctly before determining its height.
    $(this.document.body).width(w);
    h = this.document.body.offsetHeight;
    //h = h ? this.document.body.offsetHeight : 480;
  
    this.scrolling = scrolling;
    this.border = 0;
    // Hide scroll bars in webkit/mozilla.
    if (!$.browser.msie) {
      $(this.document.body).css('overflow', (scrolling == 'auto' ? 'auto' : 'hidden'));
    }
    $('#lightboxFrame', top.document).width(w);
    $('#lightboxFrame', top.document).height(h); 
    top.Lightbox.resizeContainer(w, h);
  }
}