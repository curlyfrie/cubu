<div id="menu" style="width:150px;float:left;">
	<a href="index.php?c=alarm">alarm</a>
</div>

<div id="content" style="float:left;">
<?php
	
	//include "inc/connect.php";
	
	$dbpath ="C:\Dokumente und Einstellungen\pinchbeck\Desktop\openframeworks\apps\examples\cubu\bin\data\\";
	$db = sqlite_open($dbpath."cubu.db");
	//sqlite_query($db, 'CREATE TABLE room (bar varchar(10))');
	$data = sqlite_query($db,"SELECT * FROM room");
	
	var_dump($data);
	
	switch($_GET['c']) {
		case 'alarm':
			echo "test";
			break;
		default:
			echo "welcome to the amazing cubu backend!<br>feel free to look around!";
			break;
	
	}
?>
</div>