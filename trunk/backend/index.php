<!DOCTYPE HTML PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html><head>


<meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
<!--
<html xmlns="http://www.w3.org/1999/xhtml"-->

	<title>Verwaltung</title>

<link rel="stylesheet" type="text/css" href="style.css" />
<script type="text/javascript" src="prototype.js"></script>
<script type="text/javascript" src="script.js"></script>
    	
</head><body>

<?php
require_once ("DBhandler.php");

?>
<div id="site">
	<div id="head"></div>
	<div id="menu">
<ul>
<li><a 
href="index.php?kunde">Kunden</a>
  </li>
<li><a 
href="index.php?service">Service</a>
  </li>
  <li><a 
href="index.php?faq">FAQ </a>
  </li>
<li><a 
href="index.php?speise">Speisekarte</a>
  </li>
<li><a 
href="index.php?wellness">Wellness</a>
  </li>

</ul></div>
<div id="content">
	
		<?php
		$dbhandler = new DBhandler();
		
if(isset($_REQUEST["kunde"]))
{
	echo "<h1>Kunden</h1>";
	$dbhandler->printKunden();
}
	
else if(isset($_REQUEST["faq"]))
{
	echo "<h1>FAQ</h1>";
		$dbhandler->printFaq();
}


else if(isset($_REQUEST["service"]))
{
	echo "<h1>Service</h1>";
	$dbhandler->printService();
}
	
else if(isset($_REQUEST["speise"]))
{
	echo "<h1>Speisekarte</h1>";
	echo "<h2>Getränke</h2>";
	
	$dbhandler->printGetraenke();
	echo "<h2>Speisen</h2>";
	$dbhandler->printSpeisen();
	
}
	
else if(isset($_REQUEST["wellness"]))
	{
		echo "<h1>Wellness</h1>";
	
	$dbhandler->printWellness();
	}


else if(isset($_REQUEST["terminal"]))
	$dbhandler->printTerminal($_REQUEST["terminal_id"]);
else
{
	echo "<h1>Herzlich willkommen im Admin Interface!</h1>";
	echo "<p>Die Navigation erfolgt durch die Menüleiste oben.</p>";
}
	
	
		?>
	
	
	
	</div>
	<div id="footer"></div>
</div>

</body>
</html>
