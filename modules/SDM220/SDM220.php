<?php
if($_GET["target"] == "data")
{
$SDM220_data_dir = "../../tmpfs/SDM220";
$SDM220_files = scandir($SDM220_data_dir);
header("Content-Type: text/xml; charset=us-ascii");
echo file_get_contents($SDM220_data_dir."/".$SDM220_files[count($SDM220_files) - 1]);
}
else
{
	if($_GET["target"] == "mini")
	{
		header("Content-Type: text/html; charset=UTF-8");
		require "mini-SDM220.html";
	}
	else
	{
		header("Content-Type: text/html; charset=UTF-8");
		require "SDM220.html";
	}
}
?>