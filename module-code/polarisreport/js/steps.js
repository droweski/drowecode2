
(function ($) {
 
//Inserted code 

/* Add prev/next arrows to vertical tabs. */
  $("#edit-next").click(function(e) {
    e.preventDefault();
    $(".vertical-tabs-panes fieldset:visible").hide().next('fieldset').show();
    $(".vertical-tabs-list li.selected").removeClass('selected').next('li').addClass('selected');
    $('html,body').animate({scrollTop: (0)}, 500);
    if (!$(".vertical-tabs-panes fieldset:visible").next('fieldset').length) {
      $("#edit-next").hide();
    }
    if ($(".vertical-tabs-panes fieldset:visible").prev('fieldset').length) {
      $("#edit-prev").show();
    }
    return false;
  });
  $("#edit-prev").click(function(e) {
    e.preventDefault();
    $(".vertical-tabs-panes fieldset:visible").hide().prev('fieldset').show();
    $(".vertical-tabs-list li.selected").removeClass('selected').prev('li').addClass('selected');
    $('html,body').animate({scrollTop: (0)}, 500);
    if (!$(".vertical-tabs-panes fieldset:visible").prev('fieldset').length) {
      $("#edit-prev").hide();
    }
    if ($(".vertical-tabs-panes fieldset:visible").next('fieldset').length) {
      $("#edit-next").show();
    }
    return false;
  });
  $(".vertical-tab-button a").click(function() {
    if ($(".vertical-tabs-panes fieldset:visible").prev('fieldset').length) {
      $("#edit-prev").show();
    }
    else {
      $("#edit-prev").hide();
    }
    if ($(".vertical-tabs-panes fieldset:visible").next('fieldset').length) {
      $("#edit-next").show();
    }
    else {
      $("#edit-next").hide();
    }
  });

//End of inserted code

})(jQuery);