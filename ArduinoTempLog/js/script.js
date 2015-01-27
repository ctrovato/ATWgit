$(document).ready(function() {
    $.ajax({
        url:'https://data.sparkfun.com/output/LQV28480qNhOzVpMnwRj.json',
        type: 'get',
        dataType: 'jsonp',
        crossDomain: true,
        success: function(jsonObj) {
            var tempList = $('#templist');
            var timestamp = $('#timestamp');

            $.each(jsonObj, function(i, tObj) {
              timestamp.append('<li>'  + tObj.temp + '&deg;' + ' ' + 'at' + ' ' + tObj.timestamp  + '</li>' +'<br>');
              tempList.append('<p>'  + tObj.temp + '&deg;' + '</p>');

            });
        }
    });







});