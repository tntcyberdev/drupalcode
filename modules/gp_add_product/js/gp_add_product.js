(function ($, Drupal, window, document, undefined) {
// Place your code here.
$(window).load(function(){
	$(document).ready(function() {
		$('#gp-add-product-form').validationEngine(); // Add Validate Eng
		$('#gp-add-product-edit-form').validationEngine() //Add Validate Eng
		// Click Size 
		$('.ck-size').click(function(){
			if ($(this).is(':checked')) {
				var current = $(this).parent().parent().find('.current-size').val();
				$(this).parent().parent().find('.hidden-size').val(current);
				$(this).parent().parent().parent().find('input[name^="quantity"]').val('');
				$(this).parent().parent().parent().find('input[name^="quantity"]').focus();
			} else {
				$(this).parent().parent().parent().find('input[name^="quantity"]').text('0');
				$(this).parent().parent().find('.hidden-size').val(0);
			}
		});

		// Event Click Color
		$('.ck-color').click(function(){
			var val = $(this).val();
			if ($(this).is(':checked')) {
				$('#edit-sl-color'+val).removeClass('element-invisible');
				$('#edit-sl-color'+val+' .fieldset-title').click();
			} else {
				$('#edit-sl-color'+val).addClass('element-invisible');
				$('#edit-sl-color'+val+' .fieldset-title').click();
			}
		});	

		$('.remove-img').click(function(){
			$(this).parent().remove();
		});		
	});
});
})(jQuery, Drupal, this, this.document);
