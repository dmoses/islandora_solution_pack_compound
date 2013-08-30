/**
 * @file
 *   This JS maintains the width of captions on images.
 */

/**
 * Dynamicaly alters the CSS of the thumb boxes to only be as wide as the images.
 */
function set_caption_timout() {
  setTimeout(
    function() {
      jQuery('.islandora-compound-thumb').each(
        function() {
          console.log('asdf');
          image_width = jQuery(this).find('img').outerWidth();
          jQuery(this).css('max-width', image_width);
        }
      );
    },
    250
  );
}
jQuery(document).ready(
  function() {
    window.resize_caption = set_caption_timout();
    jQuery(window).bind(
      'resize',
      function(e) {
        jQuery(window).resize(
          function() {
            clearTimeout(window.resize_caption);
            window.resize_caption = set_caption_timout();
          }
        );
      }
    );
  }
);
