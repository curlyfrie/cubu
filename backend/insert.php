<?php
require_once ("DBhandler.php");
$fields = array();
$dbhandler = new DBhandler();
while (list ($key, $value) = each ($_REQUEST))
{
	
	if($key != "table")
	{
		$fields["$key"] = $value;
	
	}
	
	 		
 		  
}

$dbhandler->insert($_REQUEST["table"], $fields);
header("location:index.php?".$_REQUEST["table"]);
?>
