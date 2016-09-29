(function($){
    $(document).ready(function(){
      var interval = null;
      rotateShowCompetition = setInterval(poll, 90000);
      rotateShowAchievement = setInterval(show_achievement, 90000);
      $('.message-group a.ctools-use-modal').click(function(){
        clearInterval(rotateShowAchievement);
        clearInterval(rotateShowCompetition);
      });
    });

    // Function Poll
    function poll() {
      var baseUrl =  Drupal.settings.basePath;
      $.ajax({
        url: baseUrl+"realtime",
        type: "GET",
        dataType: "json",
        success: function(data) {
          var output = '';
          if (data.length != "") {
            $.each(data,function(index, competion) {
              output += competion;
            });
            $('#dialog-box').html(output);
            $('#dialog-box .wrap-teaser-node-competition').dialog({
              width: 300,
              height: 'auto',
              modal: true,
            });
            stButtons.locateElements();
          } else {
            $('#dialog-box').html('');
          }
        },
        error: function(data) {
          $('#dialog-box').html('');
        },
      });
    }


    function show_achievement() {
      var baseUrl =  Drupal.settings.basePath;
      $.ajax({
        url: baseUrl+"realtime/check-achievement",
        type: "GET",
        dataType: "json",
        success: function(data) {
          if(data.length != ''){
            var output = '';
            $.each(data,function( index, achievement ) {
              output += achievement.markup;
            });
            $('#dialog-box').html(output);
           
            $.each(data,function(index, achievement ) {
              $("#node-"+achievement.id).dialog({
                  width: 300,
                  height: 'auto',
                  modal: true,
              });
            });

            stButtons.locateElements();
          }
        },
        error: function(data) {
        },
      });
    }
  
})(jQuery);