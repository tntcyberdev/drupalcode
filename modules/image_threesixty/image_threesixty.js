(function ($, Drupal, window, document, undefined) {
// Place your code here.
$(window).load(function(){
	$(document).ready(function() {
		var src_img = Drupal.settings.image_threesixty.src_img;
		var speed = Drupal.settings.image_threesixty.speed;
		$(".image-threesixty").threesixty({images:src_img, method:'auto', autoscrollspeed:speed});
	});
});
})(jQuery, Drupal, this, this.document);