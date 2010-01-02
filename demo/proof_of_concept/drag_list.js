// $Id$

Drupal.behaviors.dragList = function(context) {
  // Add Activate Drag List button to the Drag List block. 
  var blockID;
  blockID = 'div#' + Drupal.settings.drag_list.dragListBlockId;
  Drupal.settings.drag_list.currentList = $(blockID + ' div.views-field-title a.drag-list-nid').attr('title');
  
  $(blockID).append('<div class="drag-list-button"><div class="drag-list-label activate">Activate</div></div>');
  $('div.drag-list-button').click(function(){
    $(this).find('div.drag-list-label').toggle();
    dragListProcessLinks();
  });
  
  
};
/**
 * Process each link on a page, adding a class 'processed' when active.
 * The original color background of the link is stored, so it will revert
 * to the original color every time the activate button is clicked
 * (even if the background color is dynamically changed.)
 */
function dragListProcessLinks(){
  var backgroundColor;
  var highlightColor;

  highlightColor = '#ffcc00';
  $('a').each(function() {
    if($(this).is(':not(.drag-list-processed)')){
       $(this).addClass('drag-list-processed');
       backgroundColor = $(this).css('backgroundColor');
       $('a.drag-list-processed').css('backgroundColor', highlightColor);
       $(this).data('originalBackgroundColor', backgroundColor);
       
       // Add click function which loads ajax call
       $(this).bind('click', dragListStoreLink);
       
    }
    else { 
      $(this).removeClass('drag-list-processed');
      $(this).css('backgroundColor', $(this).data('originalBackgroundColor'));
      $(this).removeData('originalBackgroundColor');  
      $(this).unbind('click', dragListStoreLink);
    }
    // Strip any links from the target block.
    $('div#block-views-drag_list_blocks-block_1 a').each(function(){
      $(this).removeClass('drag-list-processed');
      $(this).css('backgroundColor', $(this).data('originalBackgroundColor'));
      $(this).removeData('originalBackgroundColor');
      $(this).unbind('click', dragListStoreLink);

    });
  });
}
function dragListStoreLink() {    
  var callback;
  callback = Drupal.settings.basePath + 'admin/drag-list/ajax/store/' + Drupal.settings.drag_list.currentList;
  $.post(callback, { link_href : $(this).attr('drag_list_value') }, dragListUpdateBlock());

  // preventing entire page from reloading 
  return false;         
}
function dragListUpdateBlock() {
  // load another callback - reload the block/view/node
}