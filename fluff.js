/**
 * @file
 * Main JS for Fluff module.
 */
(function(window, $, undefined) {
  Drupal.behaviors.fluffFormPuffSelect = function(context) {
    $('body:not(.fluff-form-puff-select-processed)').each(function() {
      $('body').addClass('fluff-form-puff-select-processed');
      $('#edit-puffs-example-puff-wrapper input').change(function() {
        var valueClass = '.fluff-form-puff-info .' + $(this).attr('value');
        if ($(this).attr('checked')) {
          $(valueClass).fadeIn('fast');
        }
        else {
          $(valueClass).fadeOut('fast');
        }
      });
    });
  };
})(window, jQuery);