(function ($, Drupal, window, document, undefined) {
// Place your code here.
$(window).load(function(){
	$(document).ready(function() {
    // Add more markup to crop image
    var obj_style = Drupal.settings.gp_image_crop.ls_style;
    var path = Drupal.settings.gp_image_crop.path;
    $('img').each(function(){
    	if ($(this).attr('typeof') == 'foaf:Image') {
	      var image = new Image();
				var src = $(this).attr('src');
				var src_arr = src.split('styles');
				if (src_arr.length > 0) {
					var src_tmp = src_arr[1].split('/');
					var style_name = src_tmp[1];
			    image.src = src;
		      var width = image.naturalWidth;
					var height = image.naturalHeight;
					if (obj_style[style_name] != 0 && (typeof obj_style !== 'undefined')){
						if (src_tmp[1] == obj_style[style_name]) {
							$(this).before('<a class = "crop-image-link" href="'+Drupal.settings.basePath+'image-crop?img='+src+'&width='+width+'&height='+height+'&path='+path+'"><i class = "icon-crop"></i> Crop</a>')
						}
					}
				}
			}
		});
	});
});
})(jQuery, Drupal, this, this.document);