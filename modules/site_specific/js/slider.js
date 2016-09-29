(function ($) {
  // Store our function as a property of Drupal.behaviors.
  Drupal.behaviors.site_specific = {
    attach: function (context, settings) {
      $(document).ready(function(){
        
        var  widget = $('#search-api-ranges-block-slider-view-form-field-total-area');

        $('#unit-area').once(function() {
          $('#unit-area').change(function() {
            var slider = widget.find('div.range-slider');
            var rangeMin = widget.find('input[name=range-min]');
            var rangeMax = widget.find('input[name=range-max]');
            var rangeFrom = widget.find('input[name=range-from]');
            var rangeTo = widget.find('input[name=range-to]');

            if ($(this).val() == 'ft2') {
              rangeFrom.val(Math.round(rangeFrom.val() * 10.7639));
              rangeTo.val(Math.round(rangeTo.val() * 10.7639));
              rangeMin.val(Math.round(rangeMin.val() * 10.7639));
              rangeMax.val(Math.round(rangeMax.val() * 10.7639));
            }else {
              rangeFrom.val(Math.round(rangeFrom.val() / 10.7639));
              rangeTo.val(Math.round(rangeTo.val() / 10.7639));
              rangeMin.val(Math.round(rangeMin.val() / 10.7639));
              rangeMax.val(Math.round(rangeMax.val() / 10.7639));
            }

            slider.slider({
              range: true,
              animate: true,
              step: 1,
              min: parseInt(rangeMin.val()),
              max: parseInt(rangeMax.val()),
              values: [parseInt(rangeFrom.val()), parseInt(rangeTo.val())],

              // on change: when clicking somewhere in the bar
              change: function(event, ui) {
                widget.find('input[name=range-from]').val(ui.values[0]);
                widget.find('input[name=range-to]').val(ui.values[1]);
              },

              // on slide: when sliding with the controls
              slide: function(event, ui) {
                widget.find('input[name=range-from]').val(ui.values[0]);
                widget.find('input[name=range-to]').val(ui.values[1]);
              }
            });

          });
        });

      });
    }
  };

}(jQuery));