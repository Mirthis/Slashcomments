// $Id$
jQuery.fn.slideFadeToggle = function(speed, easing, callback) {
  return this.animate({opacity: 'toggle', height: 'toggle'}, speed, easing, callback); 
};

if (Drupal.jsEnabled) {
  $(document).ready(function () {
   $('div.toggle_area').find('div.collapsed').hide().end().find('div.toggle_label').click(function() {
     $(this).next().slideFadeToggle("slow"); });
   });
}
