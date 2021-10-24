/*
 * Contact Class
 * by Charles French
 * for CS 320
 */


public class Contact {
private String idString;
private String firstName;
private String lastName;
private String phoneNumber;
private String address;

public static boolean isNumeric(String text) {
	// simple function to test if a string is only made of numbers, to be used for collecting phone numbers
	try {
		Double.parseDouble(text);
		return true;
	}
	catch(NumberFormatException f) {
		return false;
	}
}

public Contact(String id, String firstName, String lastName, String phoneNumber, String address) {
	if(id == null || id.length()>10) {
		throw new IllegalArgumentException("Invalid ID");
	}
	if(firstName == null || firstName.length() > 10) {
		throw new IllegalArgumentException("Invalid first name");
	}
	if(lastName == null || lastName.length() > 10)	{
		throw new IllegalArgumentException("Invalid last name");
	}
	if(phoneNumber == null || phoneNumber.length() != 10 || !isNumeric(phoneNumber)) {
		throw new IllegalArgumentException("Invalid phone number");
	}
	if(address == null || address.length() > 30) {
		throw new IllegalArgumentException("Invalid address");
	}
	
	this.idString = id;
	this.firstName = firstName;
	this.lastName = lastName;
	this.phoneNumber = phoneNumber;
	this.address = address;
}
// Class Getters
public String getId() {
	return this.idString;
}

public String getFirstName() {
	return this.firstName;
}

public String getLastName() {
	return this.lastName;
}

public String getPhoneNumber() {
	return this.phoneNumber;
}

public String getAddress() {
	return this.address;
}

// Class Setters
// ID intentionally left out

public void setFirstName(String name) {
	this.firstName = name;
}

public void setLastName(String name) {
	this.lastName = name;
}

public void setPhoneNumber(String number) {
	this.phoneNumber = number;
}

public void setAddress(String newAddress) {
	this.address = newAddress;
}
}
