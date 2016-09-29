(function ($, Drupal, window, document, undefined) {
// Place your code here.
$(window).load(function(){
	$(document).ready(function() {
		var width = $('input[name="width"]').val();
		var height = $('input[name="height"]').val();
		var default_width = 0;
		var default_height = 0;
		var current_width = default_width+parseInt(width);
		var current_height = default_height+parseInt(height);
    var ratio = width/height;

    // Action Crop Image
		$('.image-crop').Jcrop({
      aspectRatio: ratio,
      onSelect: updateCoords,
      setSelect: [ default_width, default_height, current_width, current_height],
      allowResize:true,
      allowSelect:false,
    });
	});

	function updateCoords(c) {
    $('#x').val(c.x);
    $('#y').val(c.y);
    $('#w').val(c.w);
    $('#h').val(c.h);
  };

  function checkCoords() {
    if (parseInt($('#w').val())) return true;
    alert('Please select a crop region then press submit.');
    return false;
  };

});
})(jQuery, Drupal, this, this.document);