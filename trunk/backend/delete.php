<?php
require_once ("DBhandler.php");
$dbhandler = new DBhandler();

if(isset($_REQUEST["kunde"]))
{
	
	$dbhandler->deleteKunde($_REQUEST["id"]);
}
if(isset($_REQUEST["speise"]))
{
	$dbhandler->deleteSpeise($_REQUEST["id"]);
}
if(isset($_REQUEST["service"]))
{
	$dbhandler->deleteService($_REQUEST["id"]);
}
if(isset($_REQUEST["kunde"]))
{
	$dbhandler->deleteKunde($_REQUEST["id"]);
}
if(isset($_REQUEST["faq"]))
{
	$dbhandler->deleteFaq($_REQUEST["id"]);
}

if(isset($_REQUEST["wellness"]))
{
	$dbhandler->deleteWellness($_REQUEST["id"]);
}
if(isset($_REQUEST["terminalspeise"]))
{
	$dbhandler->deleteTerminalspeise($_REQUEST["terminal_id"], $_REQUEST["speise_id"]);
}	
if(isset($_REQUEST["terminalservice"]))
{
	$dbhandler->deleteTerminalservice($_REQUEST["terminal_id"], $_REQUEST["service_id"]);
}	
?>
