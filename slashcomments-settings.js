// $Id$

Drupal.behaviors.slashcomments = function(context) {
    slashcomments_toggle_takepart();
    slashcomments_toggle_karma();
};

function slashcomments_toggle_takepart() {
  $('#edit-slashcomments-delete-takepart').attr('disabled',!$('#edit-slashcomments-limit-takepart').is(':checked'));
}

function slashcomments_toggle_karma() {
  $('#edit-slashcomments-limit-karma').attr('disabled',!$('#edit-slashcomments-enable-karma').is(':checked'));
}

