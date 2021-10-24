/*Test cases for Contact.java
 * by Charles French
 * for CS 320
 * */
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class ContactTest {

	@Test
	void testContactConstructor() {
		Contact contact = new Contact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		assertTrue(contact.getId().equals("1234567890"));
		assertTrue(contact.getFirstName().equals("John"));
		assertTrue(contact.getLastName().equals("Smith"));
		assertTrue(contact.getPhoneNumber().equals("5555555555"));
		assertTrue(contact.getAddress().equals("123 Test Street Some State USA"));
	}
	// "Too long" Tests
	@Test
	void testContactIDTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345678910", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		});
	}
	
	@Test
	void testContactFirstNameTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "John-Very-Big-Long-Name", "Smith", "5555555555", "123 Test Street Some State USA");
		});
	}
	
	@Test
	void testContactLastNameTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "John", "Mc-Way-Too-Long-Name", "5555555555", "123 Test Street Some State USA");
		});
	}
	
	@Test
	void testContactPhoneNumberTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "John", "Smith", "15555555555", "123 Test Street Some State USA");
		});
	}
	
	@Test
	void testContactAddressTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "John", "Smith", "5555555555", "123 Fake Street, Middle-of-Nowhere in Some State, USA");
		});
	}
	// "Is Null" Tests
	@Test
	void testContactIDIsNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact(null, "John", "Smith", "5555555555", "123 Test Street Some State USA");
		});
	}
	
	@Test
	void testContactFirstNameIsNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", null, "Smith", "5555555555", "123 Test Street Some State USA");
		});
	}
	
	@Test
	void testContactLastNameIsNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "John", null, "5555555555", "123 Test Street Some State USA");
		});
	}
	
	@Test
	void testContactPhoneNumberIsNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "John", "Smith", null, "123 Test Street Some State USA");
		});
	}
	
	@Test
	void testContactAddressIsNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("1234567890", "John", "Smith", "5555555555", null);
		});
	}
	
// "Setter" Tests
	@Test
	void testContactSetFirstName() {
		Contact contact = new Contact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		contact.setFirstName("Will");
		assertTrue(contact.getFirstName().equals("Will"));
	}
	
	@Test
	void testContactSetLastName() {
		Contact contact = new Contact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		contact.setLastName("Doe");
		assertTrue(contact.getLastName().equals("Doe"));
	}
	
	@Test
	void testContactSetPhoneNumber() {
		Contact contact = new Contact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		contact.setPhoneNumber("8888888888");
		assertTrue(contact.getPhoneNumber().equals("8888888888"));
	}
	
	@Test
	void testContactSetAddress() {
		Contact contact = new Contact("1234567890", "John", "Smith", "5555555555", "123 Test Street Some State USA");
		contact.setAddress("456 Newly Moved In Address USA");
		assertTrue(contact.getAddress().equals("456 Newly Moved In Address USA"));
	}
	
	//helper function test
	@Test
	void testContactIsNumericTrue() {
		String test = "5555555555";
		assertTrue(Contact.isNumeric(test) == true);
	}
	
	@Test
	void testContactIsNumericFalse() {
		String test = "555555555Five";
		assertTrue(Contact.isNumeric(test) == false);
	}
	
	@Test
	void testContactPhoneNumberNotANumber() {
		
			Assertions.assertThrows(IllegalArgumentException.class, () -> {
				new Contact("1234567890", "John", "Smith", "NotANumber", "123 Test Street Some State USA");
			});
	}
}
