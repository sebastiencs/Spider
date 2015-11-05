$(document).ready( function() {
	var data = [
	    {
	        value: $("div.container div.row.stats div.statsNumber").attr("paquetsKeys"),
	        color:"#F7464A",
	        highlight: "#FF5A5E",
	        label: "Paquets Keys"
	    },
	    {
	        value: $("div.container div.row.stats div.statsNumber").attr("paquetsMouses"),
	        color: "#46BFBD",
	        highlight: "#5AD3D1",
	        label: "Paquets Mouses"
	    },
	];
	var option = {
		percentageInnerCutout: 75,
   		responsive: true,
	    maintainAspectRatio: false
	};
	var ctx = $("#statsPaquetAll").get(0).getContext("2d");
	var myDoughnutChart = new Chart(ctx).Doughnut(data, option);
  	$("div.container div.row.statsTitle div.numberMouses h3[data-toggle='tooltip']").tooltip();
  	$("div.container div.row.statsTitle div.numberKeys h3[data-toggle='tooltip']").tooltip();
	var data = {
	    labels: ["None", "Left", "Right", "X1Button", "X2Button"],
	    datasets: [
	        {
	            fillColor: "rgba(220,220,220,0.5)",
	            strokeColor: "rgba(220,220,220,0.8)",
	            highlightFill: "rgba(220,220,220,0.75)",
	            highlightStroke: "rgba(220,220,220,1)",
	            data: [
	            	$("div.container div.row.paquetsMouses div.statsPaquetsMouses").attr("none"),
	            	$("div.container div.row.paquetsMouses div.statsPaquetsMouses").attr("left"),
	            	$("div.container div.row.paquetsMouses div.statsPaquetsMouses").attr("right"),
	            	$("div.container div.row.paquetsMouses div.statsPaquetsMouses").attr("X1Button"),
	            	$("div.container div.row.paquetsMouses div.statsPaquetsMouses").attr("X2Button")
	            ]
	        }
	    ]
	};
	var ctx = $("#statsPaquetMouses").get(0).getContext("2d");
	var myBarChart = new Chart(ctx).Bar(data, option);
});