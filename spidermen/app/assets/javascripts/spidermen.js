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
		percentageInnerCutout: 75
	};
	var ctx = $("#statsPaquet").get(0).getContext("2d");
	var myDoughnutChart = new Chart(ctx).Doughnut(data, option);
  	$("div.container div.row.stats div.numberMouses h3[data-toggle='tooltip']").tooltip();
  	$("div.container div.row.stats div.numberKeys h3[data-toggle='tooltip']").tooltip();
});