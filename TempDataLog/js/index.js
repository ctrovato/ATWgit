$(document).ready(function() {
    $.ajax({
        url:'https://data.sparkfun.com/output/LQV28480qNhOzVpMnwRj.json',
        type: 'get',
        dataType: 'jsonp',
      	data: {limit: 100, order:"desc"},
        crossDomain: true,
        success: function(jsonObj) {
            var tempList = [];
            var timestamp = [];
            var ctx = document.getElementById("canvas").getContext('2d');




            $.each(jsonObj, function(i, tObj) {
	          var newDate = new Date(tObj.timestamp);
	          formatted = newDate.getHours() + ":" + newDate.getMinutes() + ":" + newDate.getSeconds();

              timestamp.push(formatted);
              tempList.push(tObj.temp);
              console.log(tObj.tempList);
            });


var lineChartData = {
	labels: timestamp,
	datasets: [{
		fillColor: "rgba(255, 153, 0,0.5)",
		strokeColor: "rgba(220,220,220,1)",
		pointColor: "rgba(220,220,220,1)",
		pointStrokeColor: "#fff",
		data: tempList
	}]
};
var myLine = new Chart(document.getElementById("canvas").getContext("2d")).Line(lineChartData);
      }
    });
});