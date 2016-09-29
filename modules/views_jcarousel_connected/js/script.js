(function ($) { 
	jQuery(document).ready(function () {
		var connector = function(itemNavigation, carouselStage) {
        return carouselStage.jcarousel('items').eq(itemNavigation.index());
    };

    $(function() {
      $('.connected-carousels').each(function(){
        var id = $(this).attr('id');
        var carouselNavigation = $('#'+id+' .carousel-navigation').jcarousel({
          wrap: 'null',
          transitions: Modernizr.csstransitions ? {
          transforms: Modernizr.csstransforms,
          transforms3d: Modernizr.csstransforms3d,
          easing: 'ease'
          } : false,
          animation: {
            duration: 1000,
            easing:   'linear',
            complete: function() {
            }
          }
        });
        // Setup controls for the navigation carousel
        $('#'+id+' .prev-navigation')
          .on('jcarouselcontrol:inactive', function() {
            $('#'+id).find('.prev-navigation').addClass('inactive');
          })
          .on('jcarouselcontrol:active', function() {
            $('#'+id).find('.prev-navigation').removeClass('inactive');
          })
          .jcarouselControl({
            target: '-=4'
          });

        $('#'+id+' .next-navigation')
          .on('jcarouselcontrol:inactive', function() {
            $('#'+id).find('.next-navigation').addClass('inactive');
          })
          .on('jcarouselcontrol:active', function() {
            $('#'+id).find('.next-navigation').removeClass('inactive');
          })
          .jcarouselControl({
            target: '+=4'
          });
         
      }); 
    }); 

	});
})(jQuery);