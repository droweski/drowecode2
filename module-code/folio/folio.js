
(function ($) {

Drupal.behaviors.folioFieldsetSummaries = {
  attach: function (context) {
    $('fieldset.folio-form', context).drupalSetSummary(function (context) {
      var val = $('.form-item-folio-bid select').val();

      if (val === '0') {
        return Drupal.t('Not in folio');
      }
      else if (val === 'new') {
        return Drupal.t('New folio');
      }
      else {
        return Drupal.checkPlain($('.form-item-folio-bid select :selected').text());
      }
    });
  }
};

})(jQuery);
