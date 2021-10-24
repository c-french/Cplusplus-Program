/*Contact Service Class
 * by Charles French
 * for CS 320
 * 
 */
import java.util.ArrayList;
import java.util.Iterator;

public class ContactService {
ArrayList<Contact> contacts = new ArrayList<Contact>();



public void addContact(String id, String firstName, String lastName, String phoneNumber, String address) {
	// create new contact object, add to contacts list
	// parsing is handled in the Contact class constructor
	Contact contact = new Contact(id, firstName, lastName, phoneNumber, address);
	contacts.add(contact);
}

public void removeContact(String id) {
	//search contacts for matching id, then remove it
	// search contact array for match
	Iterator<Contact> it = contacts.iterator();
	boolean isFound = false;
	
	while(it.hasNext()) {
		Contact temp = it.next();
		if(temp.getId().equals(id)) {
			it.remove();
			isFound = true;
		}
	}
	
	// notify user of success/fail to find
	if(isFound) {
		System.out.println("Contact removed!");
	}else {
		System.out.println("Contact not found.");
	}
}

public void updateContact(String id, int option, String newInput) {
	//validate string
	if(id == null || id.length() > 10) {
		throw new IllegalArgumentException("Invalid ID");
	}
	//validate newInput string, considering case of address change
	if((option != 4 && newInput.length() > 10) || (option == 4 && newInput.length() > 30)) {
		throw new IllegalArgumentException("Invalid entry");
	}
	
	// loop through arraylist to find a match
	Iterator<Contact> it = contacts.iterator();
	
	while(it.hasNext()) {
		Contact temp = it.next();
		// per option choice, call appropriate Contact setter
		if(temp.getId().equals(id)) {
			switch (option) {
				case 1: //first name
					temp.setFirstName(newInput);
					break;
				case 2: //last name
					temp.setLastName(newInput);
					break;
				case 3: //phone number
					temp.setPhoneNumber(newInput);
					break;
				case 4: //address
					temp.setAddress(newInput);
					break;
				default: //anything else would be an error
					throw new IllegalArgumentException("Invalid option");
			}
		}
	}
}
}
