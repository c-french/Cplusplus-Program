/* ContactService Test Cases for ContactService.java
 * by Charles French
 * for CS 320
 * 
 * */
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Iterator;
class ContactServiceTest {

	@Test
	void testContactServiceAddContact() {
		ContactService test = new ContactService();
		test.addContact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		Iterator<Contact> it = test.contacts.iterator();
		Contact temp = it.next();
		assertTrue(temp.getId().equals("1234567890"));
		assertTrue(temp.getFirstName().equals("John"));
		assertTrue(temp.getLastName().equals("Smith"));
		assertTrue(temp.getPhoneNumber().equals("5555555555"));
		assertTrue(temp.getAddress().equals("123 Test Street Some State USA"));
	}

	@Test
	void testContactServiceRemoveContactInArray() {
		ContactService test = new ContactService();
		test.addContact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		test.addContact("0987654321", "Jane", "Doe", "4444444444", "765 Test Street Some State USA");
		test.removeContact("1234567890");
		Iterator<Contact> it = test.contacts.iterator();
		Contact temp = it.next();
		assertTrue(temp.getId().equals("0987654321"));
		assertTrue(temp.getFirstName().equals("Jane"));
		assertTrue(temp.getLastName().equals("Doe"));
		assertTrue(temp.getPhoneNumber().equals("4444444444"));
		assertTrue(temp.getAddress().equals("765 Test Street Some State USA"));
	}
	
	@Test
	void testContactServiceUpdateFirstName() {
		ContactService test = new ContactService();
		test.addContact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		test.updateContact("1234567890", 1, "Jake");
		Iterator<Contact> it = test.contacts.iterator();
		if(it.hasNext()) {
			Contact temp = it.next();
			assertTrue(temp.getFirstName().equals("Jake"));
		}
		
	}
	
	@Test
	void testContactServiceUpdateLastName() {
		ContactService test = new ContactService();
		test.addContact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		test.updateContact("1234567890", 2, "Deer");
		Iterator<Contact> it = test.contacts.iterator();
		if(it.hasNext()) {
			Contact temp = it.next();
			assertTrue(temp.getLastName().equals("Deer"));
		}
		
	}
	
	@Test
	void testContactServiceUpdatePhoneNumber() {
		ContactService test = new ContactService();
		test.addContact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		test.updateContact("1234567890", 3, "4444444444");
		Iterator<Contact> it = test.contacts.iterator();
		if(it.hasNext()) {
			Contact temp = it.next();
			assertTrue(temp.getPhoneNumber().equals("4444444444"));
		}
		
	}
	
	@Test
	void testContactServiceUpdateAddress() {
		ContactService test = new ContactService();
		test.addContact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		test.updateContact("1234567890", 4, "456 Just Moved Somewhere Else");
		Iterator<Contact> it = test.contacts.iterator();
		if(it.hasNext()) {
			Contact temp = it.next();
			assertTrue(temp.getAddress().equals("456 Just Moved Somewhere Else"));
		}
		
	}
	
	@Test
	void testContactServiceUpdateContactBadID() {
		ContactService test = new ContactService();
		test.addContact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			test.updateContact("12345678910", 1, "Jake");;
		});
	}	
	
	@Test
	void testContactServiceUpdateContactBadOption() {
		ContactService test = new ContactService();
		test.addContact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			test.updateContact("1234567890", 5, "Jake");;
		});
	}
	
	@Test
	void testContactServiceUpdateContactBadAddress() {
		ContactService test = new ContactService();
		test.addContact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			test.updateContact("1234567890", 4, "A very long address that should throw an exception");;
		});
	}
	
	private final ByteArrayOutputStream out = new ByteArrayOutputStream();
	private final PrintStream originalOut = System.out;
	
	@BeforeEach
	void setStream() {
		System.setOut(new PrintStream(out));
	}
	
	@AfterEach
	void restoreStream() {
		System.setOut(originalOut);
	}
	@Test
	void testContactServiceRemoveContactNotInArray() {
		ContactService test = new ContactService();
		test.addContact("0987654321", "Jane", "Doe", "4444444444", "765 Test Street Some State USA");
		test.removeContact("1234567890");
		assertEquals("Contact not found.\r\n", out.toString());
	}
	
	
	
}
