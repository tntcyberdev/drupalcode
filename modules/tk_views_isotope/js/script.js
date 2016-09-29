(function ($) {
// Store our function as a property of Drupal.behaviors.
Drupal.behaviors.tk_views_isotope = {
  attach: function (context, settings) {
    $(document).ready(function(){
      $('a.filter').click(function(){
				$('a.filter').each(function(){
					$('a.filter').removeClass('active');
				});
				$(this).addClass('active');
				var selector = $(this).attr('data-filter');
				$('.gallery-isotope').isotope({ filter: selector }); //List Project
				return false;
			});		

			// Add isotope jQuery
			$('.gallery-isotope').addClass('variable-sizes');
			$('.gallery-isotope').isotope({
				itemSelector : 'li',
				masonry: {
				  columnWidth: Drupal.settings.tk_views_isotope.width_item,
				},
	      resizesContainer: true
			});

			$('.gallery-isotope').isotope({ filter: '*' }); //Set Default
    });
  }
};

}(jQuery));