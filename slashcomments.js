// $Id$
jQuery.fn.slideFadeToggle = function(speed, easing, callback) {
  return this.animate({opacity: 'toggle', height: 'toggle'}, speed, easing, callback); 
};

Drupal.behaviors.slashcomments = function(context) {
   $('div.toggle_area').find('div.collapsed').hide().end().find('div.toggle_label').click(function() {
     $(this).next().slideFadeToggle("slow");});

  $("form[id^='slashcomments-moderation-form']").submit(function() {
    var vote = $(this).find('select').val()
    var cid = $(this).find("input[name = 'cid']").val();
    var uid = $(this).find("input[name = 'uid']").val();
    var form_id = $(this).attr('id');

    var moderated = function (data) {
        var form_obj = $('#'+form_id);

        $(form_obj).find('div.scomments_loader').empty();

        $(form_obj).find('div.scomments_form').slideToggle(300, function(){
            $(form_obj).find('div.scomments_form_status').html(data.status).slideDown(300);
        });

        $('#comment-'+cid).find('.scomments_rating').fadeOut("slow", function() {
            $(this).empty().html(data.rating).fadeIn();
        });
    }

    var error_handler = function(xhr, ajaxOptions, thrownError) {
        var form_obj = $('#'+form_id);

        $(form_obj).find('div.scomments_loader').empty();
        $(form_obj).find('div.scomments_form_status').html(Drupal.settings.slashdot.error_status).css('display','inline');
        $(form_obj).find('select').attr("disabled", "");
        $(form_obj).find('input').attr("disabled", "");
    }

    $(this).find('select').attr("disabled", "true");
    $(this).find('input').attr("disabled", "true");
    $(this).find('div.scomments_form_status').css('display','none');
    $(this).find('div.scomments_loader').html('<img src="'+Drupal.settings.slashdot.load_image_path+'"/>');

    $.ajax({
        type: 'POST',       // Use the POST method.
        url: Drupal.settings.baseUrl+'/slashdot/moderate',
        data: 'js=1&cid='+cid+'&uid='+uid+'&vote='+vote,
        dataType: 'json',
        error:  error_handler,
        success: moderated
    })
    return false;
  });

};