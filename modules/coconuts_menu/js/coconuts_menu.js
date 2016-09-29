jQuery(document).ready(function ($) {
	var tid_ = $('.list-main-menu-view .views-row-1 .tid-source').attr('data-tid');
	$('.region-sub-menu').attr('data-tid',tid_);

	// Add jCarousel
	var jcarousel = $('.wrapper-submenu').jcarousel({
		wrap: 'both',
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
	$('.jcarousel-control-prev')
    .jcarouselControl({
        target: '-=6'
    });

	$('.jcarousel-control-next')
    .jcarouselControl({
        target: '+=6'
    });
    
  // Menu hover
	$('.main-menu-view li').mouseenter(function(){
		$('.list-main-menu-view li').removeClass('active');
		var tid = $(this).find('.tid-source').attr('data-tid');
		var output = load_Storage(tid);
		if (!output) {
			load_content(tid);
		} else {
			$('.block-view-video-menu').html(output);
			// Add SVG tag
			var svg_html = '<svg class="icon-player-svg" data-svg-fallback-override="" data-svg-fallback="/v/eater/scripts/../images/ui/play-button.png" viewBox="0 0 12.4 12.4" height="100" width="100" xmlns="http://www.w3.org/2000/svg"><circle class="shape-1" r="6.2" cy="6.2" cx="6.2" fill="#fff" opacity="1"/><path class="shape-2" d="M4.6 3.5l4.1 2.7-4.1 2.7z" fill="#10d14a"/></svg>';
			$('.block-view-video-menu .group-img-duration .views-field-field-image-video > a').append(svg_html);
			$('.region-sub-menu').show();
			$('.region-sub-menu').attr('data-tid',tid);
			$('.wrapper-submenu').jcarousel({
				wrap: 'both',
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

			$('.jcarousel-control-prev')
		    .jcarouselControl({
		        target: '-=6'
		    });

			$('.jcarousel-control-next')
		    .jcarouselControl({
		        target: '+=6'
		    });
		}
		return false;
	});
	// Menu mouse leave
	$('.main-menu-view li').mouseleave(function(){
		$('.region-sub-menu').hide();
	});

	$(".region-sub-menu").hover(function() {
		$('.region-sub-menu').show();
		var tid = $(this).attr('data-tid');
		$('.list-main-menu-view li').removeClass('active');
		$('.list-main-menu-view .tid-source').each(function(){
			if (tid == $(this).attr('data-tid')) {
				$(this).parent().parent().addClass('active');
			}
		});
	}, function() {
		$('.region-sub-menu').hide();
		$('.list-main-menu-view li').removeClass('active');
	}
	);

	// Function Load more
	function load_content(index){
		var key = index;
		$('.block-view-video-menu').html('<span class = "icon-loading"><img src = "/sites/all/themes/coconuts_tv/images/loader64.gif" /></span>');
		$('.region-sub-menu').show();
		jQuery.ajax({
			type: "POST",
			url: Drupal.settings.basePath+"get-video",
			dataType: 'json',
			data:{
				index:index,
			},
			success: function (data) {
				save_Storage(key, data, 30);
				$('.block-view-video-menu').html(data);
				var svg_html = '<svg class="icon-player-svg" data-svg-fallback-override="" data-svg-fallback="/v/eater/scripts/../images/ui/play-button.png" viewBox="0 0 12.4 12.4" height="100" width="100" xmlns="http://www.w3.org/2000/svg"><circle class="shape-1" r="6.2" cy="6.2" cx="6.2" fill="#fff" opacity="1"/><path class="shape-2" d="M4.6 3.5l4.1 2.7-4.1 2.7z" fill="#10d14a"/></svg>';
				$('.block-view-video-menu .group-img-duration .views-field-field-image-video > a').append(svg_html);
				$('.region-sub-menu').show();
				$('.wrapper-submenu').jcarousel({
					wrap: 'both',
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

				$('.jcarousel-control-prev')
			    .jcarouselControl({
			        target: '-=6'
			    });

				$('.jcarousel-control-next')
			    .jcarouselControl({
			        target: '+=6'
			    });
			}
		});
	}

	function save_Storage(index,data,expirationMin) {
		if (!Modernizr.localstorage){ return false;}
		var expirationMS = expirationMin * 60 * 1000;
    var record = {value: JSON.stringify(data), timestamp: new Date().getTime() + expirationMS};
    localStorage.setItem(index, JSON.stringify(record));
    return data;
	}
	// Function load storage use Modernizr
	function load_Storage(index) {
		if (!Modernizr.localstorage){return false;}
    var record = JSON.parse(localStorage.getItem(index));
    if (!record){return false;}
    return (new Date().getTime() < record.timestamp && JSON.parse(record.value));
	}
});
