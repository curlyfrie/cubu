function deleteElement(type, id){
	if (confirm('Wollen Sie den Eintrag wirklich loeschen?' )) {
		
		new Ajax.Request("delete.php?"+type+"&id=" + id);
		window.location.reload();
		
		//show_questions();
	}
}


function delete_terminalspeise(terminal_id, speise_id){
	if (confirm('Wollen Sie den Eintrag wirklich loeschen?' )) {
		new Ajax.Request("delete.php?terminalspeise&terminal_id=" + terminal_id + "&speise_id=" +speise_id);
		window.location.reload();
		
		//show_questions();
	}
}

function delete_terminalservice(terminal_id, service_id){
	if (confirm('Wollen Sie den Eintrag wirklich loeschen?' )) {
		
		new Ajax.Request("delete.php?terminalservice&terminal_id=" + terminal_id + "&service_id=" +service_id);
		window.location.reload();
		
		//show_questions();
	}
}

