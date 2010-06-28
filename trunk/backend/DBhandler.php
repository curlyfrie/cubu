<?php
class DBhandler {
	var $connection;
	var $db;

	function DBhandler() {
		$this->connection = mysql_connect("spanish-jewelry.com", "d00e2d6b", "9x69rLHnf4K4yQrg");
		$this->db = mysql_select_db("d00e2d6b");

	}
	function insert($tablename, $fields) {

		$sql = "INSERT INTO $tablename (";
		$i = 0;

		foreach ($fields as $field => $value) {
			$sql .= " $field ";
			$i++;
			if ($i < count($fields))
				$sql .= ", ";

		}

		$sql .= ") VALUES ( ";

		$i = 0;
		foreach ($fields as $field => $value) {
			$sql .= "  '$value' ";
			$i++;
			if ($i < count($fields))
				$sql .= ", ";

		}
		$sql .= ")";
		mysql_query($sql);

	}
	function deleteFaq($id) {
		$sql = "DELETE FROM faq WHERE faq_id = $id";

		mysql_query($sql);

	}
	function deleteDienstleistung($id) {
		$sql = "DELETE FROM dienstleistung WHERE dienst_id = $id";
		mysql_query($sql);

	}

	function deleteAlarmByTerminal($terminal_id) {
		$sql = "DELETE FROM alarm WHERE terminal_id = $terminal_id";
		mysql_query($sql);

	}

	function deleteKunde($id) {
		$sql = "DELETE FROM kunde WHERE kunde_id = $id";
		mysql_query($sql);
		$sql = "DELETE FROM terminalkunde WHERE kunde_id = $id";
		mysql_query($sql);
	}

	function deleteSpeise($id) {
		$sql = "DELETE FROM speise WHERE speise_id = $id";
		mysql_query($sql);
	}

function deleteService($id) {
		$sql = "DELETE FROM service WHERE service_id= $id";
		
		mysql_query($sql);
	}
	function deleteWellness($id) {
		$sql = "DELETE FROM wellness WHERE wellness_id = $id";
		mysql_query($sql);
	}

	

	function deleteTerminalspeise($terminal_id, $speise_id) {
		$sql = "DELETE FROM terminalspeise WHERE terminal_id = $terminal_id and speise_id = $speise_id";
		mysql_query($sql);
	}
	function deleteTerminalservice($terminal_id, $service_id) {
		$sql = "DELETE FROM terminalservice WHERE terminal_id = $terminal_id and service_id = $service_id";
		mysql_query($sql);
	}
	function printFaq() {
		$sql = "SELECT *
			FROM faq
			";

		$res = mysql_query($sql);

		while ($row = $this->getRow($res)) {
			echo "<h2>" . $row["frage"] . "</h2>";
			echo "<p>" . $row["antwort"] . "</p><p><a href=# onclick=deleteElement(\"faq\"," . $row["faq_id"] . ")>löschen</a></p>";
		}

		echo "<form action=insert.php>
	<h3>Neue Frage einfügen</h3>
			<table><tr><td>Frage</td><td><input type=text name=frage></td></tr>
				<tr><td>Antwort</td><td><textarea name=antwort></textarea></td></tr>
	</table><input type=hidden name=table value=faq>
		<input type=submit value='einfügen'></form>";

	}

	function printSpeisen() {
		$sql = "SELECT *
			FROM speise where typ = 0
			";

		$res = mysql_query($sql);

		echo "<form action=insert.php><table>
			<tr>
			<th>Name</th>
			<th>Beschreibung</th>
	<th>Preis (EUR)</th>
<th>Bild URL</th>

	<th></th>
	
			</tr>";
		while ($row = $this->getRow($res)) {
			echo "<tr><td>" . $row["name"] . "</td>";
			echo "<td>" . $row["beschreibung"] . "</td>";
			echo "<td>" . $row["preis"] . "</td>";
echo "<td>" . $row["bild"] . "</td>";

			echo " <td><a href=# onclick=deleteElement(\"speise\"," . $row["speise_id"] . ")>löschen</a></td></tr>";

		}
		echo "<tr><td><input type=text name=name></td><td><input type=text name=beschreibung style='width:95%'></td><td><input type=text name=preis style='width:50%'></td><td><input type=text name=bild></td><td><input type=submit value=neu></td></tr>";
		echo "</table><input type=hidden name=table value=speise></form>";

	}

	function printGetraenke() {
		$sql = "SELECT *
			FROM speise where typ = 1
			";

		$res = mysql_query($sql);

		echo "<form action=insert.php><table>
			<tr>
			<th>Name</th>
			<th>Beschreibung</th>
	<th>Preis (EUR)</th>
	<th>Bild URL</th>

	<th></th>
	
			</tr>";
		while ($row = $this->getRow($res)) {
			echo "<tr><td>" . $row["name"] . "</td>";
			echo "<td>" . $row["beschreibung"] . "</td>";
			echo "<td>" . $row["preis"] . "</td>";
			echo "<td>" . $row["bild"] . "</td>";
			echo " <td><a href=# onclick=deleteElement(\"speise\"," . $row["speise_id"] . ")>löschen</a></td></tr>";

		}
		echo "<tr><td><input type=text name=name></td><td><input type=text name=beschreibung style='width:95%'></td><td><input type=text name=preis  style='width:50%'></td><td><input type=text name=bild></td><td><input type=submit value=neu></td></tr>";
		echo "</table><input type=hidden name=typ value=1><input type=hidden name=table value=speise></form>";

	}

	function printService() {
		$sql = "SELECT *
			FROM service
			";

		$res = mysql_query($sql);

		echo "<form action=insert.php>
<table><tr><th>Name</th>
	<th>Beschreibung</th>
	
	
	
	</tr>";
		while ($row = $this->getRow($res)) {
			echo "<tr><td>" . $row["name"] . "</td>";
			echo "<td>" . $row["beschreibung"] . "</td>";
echo "<td><a href=# onclick=deleteElement(\"service\",".$row["service_id"].") >löschen</a></td></tr>";

		}
		echo "<tr><td><input type=text name=name></td><td><input type=text name=beschreibung style='width:95%' ></td>
		<td><input type=submit value=neu></td></tr>";
		echo "</table><input type=hidden name=table value=service></form>";

		

	}
	
	function printWellness() {
		$sql = "SELECT *
			FROM wellness
			";

		$res = mysql_query($sql);

		echo "<form action=insert.php>
<table><tr><th>Name</th>
	<th>Beschreibung</th>
	<th>Priorität</th>
<th>Preis</th>
<th>Typ</th>
	
	
	</tr>";
		while ($row = $this->getRow($res)) {
			echo "<tr><td>" . $row["name"] . "</td>";
			echo "<td>" . $row["beschreibung"] . "</td>";
echo "<td>" . $row["prioritaet"] . "</td>";
echo "<td>" . $row["preis"] . "</td>";
echo "<td>" . $row["typ"] . "</td>";
echo "<td><a href=# onclick=deleteElement(\"wellness\",".$row["wellness_id"].") >löschen</a></td></tr>";

		}
		echo "<tr><td><input type=text name=name ></td><td><input type=text name=beschreibung ></td><td><input type=text name=preis style='width:20px'></td>
<td><input type=text name=prioritaet style='width:20px'></td><td><input type=text name=typ style='width:20px'></td>
		<td><input type=submit value=neu></td></tr>";
		echo "</table><input type=hidden name=table value=wellness></form>";

	}
	function printTerminal($terminal_id) {
		$sql = "select vorname, nachname from kunde natural join terminalkunde where terminal_id =$terminal_id";
		$res = mysql_query($sql);
		
			while ($row = $this->getRow($res)) {
				echo "<h1>Abwicklung " . $row["vorname"] . " " . $row["nachname"] . "</h1>";
			}
			$sql = "SELECT s.service_id, ts.terminal_id, s.name, datum FROM terminalservice ts
				natural join service  s
				where ts.terminal_id =$terminal_id ";

			$res = mysql_query($sql);
			echo "<h2>Services</h2>";
			if (mysql_num_rows($res) > 0) {
			echo "<table><tr><th>Bestelldatum</th><th>Was?</th><th></th></tr>";
			while ($row = $this->getRow($res)) {
				echo "<tr><td>" . $row["datum"] . "</td><td>" . $row["name"] . "</td><td><a href=# onclick=\"delete_terminalservice(" . $row["terminal_id"] . ", " . $row["service_id"] . ")\" >erledigt?</a></td></tr>";
			}
			echo "</table>";
		} else
			echo "<p>Keine offenen Services.</p>";

		$sql = "SELECT s.name, s.speise_id, ts.terminal_id, ts.anzahl, ts.datum, ts.sumpreis FROM terminalspeise ts  
			natural join speise s
			where ts.terminal_id =$terminal_id ";

		$res = mysql_query($sql);
		echo "<h2>Offene Speisen/Getränke</h2>";
		if (mysql_num_rows($res) > 0) {
		echo "<table>";
		echo "<tr><th>Bestellzeit</th><th>Was?</th>";
		while ($row = $this->getRow($res)) {
			echo "<tr><td>" . $row["datum"] . "</td><td>" . $row["anzahl"] . " " . $row["name"] . "</td>
				<td><a href=# onclick=\"delete_terminalspeise(" . $row["terminal_id"] . ", " . $row["speise_id"] . ")\" >geliefert?</a></td>
				</tr>";
		}
		echo "</table>";
		}
		else echo"<p> Keine offenen Speisen/Getränke.</p>";
		
		
		
			$sql = "SELECT w.name,  tw.datum FROM terminalwellness tw  
			INNER JOIN wellness w on tw.wellness_id = w.wellness_id
			where tw.terminal_id =$terminal_id ";

		$res = mysql_query($sql);
		echo "<h2>Wellness-Dienstleistungen</h2>";
		if (mysql_num_rows($res) > 0) {
		echo "<table>";
		echo "<tr><th>Bestellzeit</th><th>Was?</th>";
		while ($row = $this->getRow($res)) {
			echo "<tr><td>" . $row["datum"] . "</td><td>" .  $row["name"] . "</td>
				<td><a href=# onclick=\"delete_terminalspeise(" . $row["terminal_id"] . ", " . $row["speise_id"] . ")\" >geliefert?</a></td>
				</tr>";
		}
		echo "</table>";
		}
		else echo"<p> Keine offenen Wellness-Dienstleistungen.</p>";
	}

	function printKunden() {
		$sql = "SELECT t.terminal_id, k.kunde_id , k.vorname, k.nachname, k.adresse, k.kreditkartennummer, tk.von, tk.bis, t.zimmer, t.telefonnummer
			FROM kunde k 
			LEFT JOIN terminalkunde	tk ON k.kunde_id = tk.kunde_id 
			LEFT JOIN terminal t ON tk.terminal_id = t.terminal_id";

		$res = mysql_query($sql);

		echo "<table>";
		echo "<tr>";
		echo "<th>Vorname</th>";
		echo "<th>Nachname</th>";
		echo "<th>Zimmer</th>";
		//echo "<th>Kreditkartennr</th>";
		//echo "<th>check in </th>";
		//echo "<th>check out</th>";
		echo "<th>Tel.</th>";
		echo " <th></th>
			</tr>";

		while ($row = $this->getRow($res)) {
			echo "<tr>";
			if($row["terminal_id"] != "")
			{
				echo "<td><a href=index.php?terminal&terminal_id=" . $row["terminal_id"] . ">" . $row["vorname"] . "</a></td>";
				echo "<td><a href=index.php?terminal&terminal_id=" . $row["terminal_id"] . ">" . $row["nachname"] . "</a></td>";
			
			}
			else {
			echo "<td> " . $row["vorname"] . "</td>";
			echo "<td>" . $row["nachname"] . "</td>";
				
			}
			
			//echo "<td>" . $row["adresse"] . "</td>";
			//echo "<td>" . $row["kreditkartennummer"] . "</td>";
			//echo "<td>" . $row["von"] . "</td>";
			//echo "<td>" . $row["bis"] . "</td>";
			
			if($row["zimmer"] != "")
			{
					echo "<td>".$row["zimmer"]."</td>";
			}
				
			else
			{
				echo "<td>kein Zi. zugeordnet</td>";
				
			}
				
			echo "<td>" . $row["telefonnummer"] . "</td>";

			echo "<td><a href=# onclick=deleteElement(\"kunde\"," . $row["kunde_id"] . ")>löschen</a></td>";
			echo "</tr>";
		}
		echo "</table><h2>Neuer Kunde</h2>
<form action=insert.php><table id=neukunde>
	<tr><td>Vorname</td><td><input type=text name=vorname></td></tr>
<tr><td>Nachname</td><td><input type=text name=nachname></td></tr>
<tr><td>Adresse</td>	<td><input type=text name=adresse></td></tr>
<tr><td>Kreditkartennr</td><td><input type=text name=kreditkartennummer></td></tr>
	<tr><td></td><td><input type=submit value=neu></td></tr>";
		echo "</table><input type=hidden name=table value=kunde></form>";

	}
	function getRow($res) {
		return mysql_fetch_assoc($res);
	}

}
?>