

import static org.junit.Assert.assertEquals;

import junit.framework.TestCase;
//import 

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   /*public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //The first parameter is the EXPECTED value and we are asserting it against
	   //the returned value from isValid().
	   assertEquals(true, urlVal.isValid("http://www.google.com"));
	   assertEquals(false, urlVal.isValid("http://www.google.com:80/test/index.html"));
	   assertEquals(false, urlVal.isValid("http://google.com///test1"));
	   
   }*/
   
   //Partiton source: https://en.wikipedia.org/wiki/URL
   
   /*public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //The first partition tests the AUTHORITY validation of isValid().
	   assertEquals(true, urlVal.isValid("http://www.google.com"));
	   assertEquals(true, urlVal.isValid("http://.google.com"));
	   assertEquals(true, urlVal.isValid("http://google.com"));
	   assertEquals(false, urlVal.isValid("http://23r2.google.com")); //bug?
	   
   }*/
   
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //The second partition tests the SCHEME validation of isValide().
	   String testString;
	   
	   String[] trueSchemes = {"http://", 
			   					""};
	   
	   String[] falseSchemes = {"3htp://", 
			   					"http//", 
			   					"http:/", 
			   					"http:", 
			   					"://"};
	   
	   String otherParts = "www.google.com";
	   
	   System.out.println();
	   System.out.println("-----Second Partition: Schemes-----");
	   
	   //test isValid() with supposedly valid URL's
	   for (int i = 0; i < trueSchemes.length; i++) {
		   
		   testString = trueSchemes[i] + otherParts;
		   
		   boolean result = urlVal.isValid(testString);
		   
		   System.out.println("\"" + trueSchemes[i]+ "\"" + "--	Expected: true;	Actual Result: " + result);
		   
		   testString = "";
	   }
	   
	   //test isValid() with supposedly invalid URL's
	   for (int j = 0; j < falseSchemes.length; j++) {
		   
		   testString = falseSchemes[j] + otherParts;
		   
		   boolean result = urlVal.isValid(testString);
		   
		   System.out.println("\"" + falseSchemes[j]+ "\"" + "--	Expected: false;	Actual Result: " + result);
		   
		   testString = "";
	   }
	   
   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testYourThirdPartition(){
		 //You can use this function to implement your Second Partition testing
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //The second partition tests the PATH validation of isValide().
	   String testString;
	   String prefix = "http://www.google.com";
	   
	   String[] truePath = {"", 
			   				"/test1", 
			   				"/test1/", 
			   				"/t123", 
			   				"/123", 
			   				"/$23"};
	   
	   String[] falsePath = {"/..", 
			   					"/../", 
			   					"//.", 
			   					"//.//", 
			   					"/test1//file", 
			   					"//test/file"};
	   
	   
	   System.out.println();
	   System.out.println("-----Third Partition: Path-----");
	   
	   //test isValid() with supposedly valid URL's
	   for (int i = 0; i < truePath.length; i++) {
		   
		   testString = prefix + truePath[i];
		   
		   boolean result = urlVal.isValid(testString);
		   
		   System.out.println("\"" + testString + "\"" + "--	Expected: true;	Actual Result: " + result);
		   
		   testString = "";
	   }
	   
	   //test isValid() with supposedly invalid URL's
	   for (int j = 0; j < falsePath.length; j++) {
		   
		   testString = prefix + falsePath[j];
		   
		   boolean result = urlVal.isValid(testString);
		   
		   System.out.println("\"" + testString + "\"" + "--	Expected: false;	Actual Result: " + result);
		   
		   testString = "";
	   }
	   
 }
   
   
   public void testYourForthPartition(){
		 //You can use this function to implement your Second Partition testing
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //The second partition tests the QUERY validation of isValide().
	   String testString;
	   String prefix = "http://www.google.com/";
	   
	   String[] trueQuery = {"", 
			   				"?action=edit", 
			   				"?action=edit&mode=up", 
			   				"?action=edit&ampmode=up"};
	   
	   String[] falseQuery = {"@action=edit", 
			   					"!action=edit", 
			   					"&action=edit"};
	   
	   
	   System.out.println();
	   System.out.println("-----Forth Partition: Query-----");
	   
	   //test isValid() with supposedly valid URL's
	   for (int i = 0; i < trueQuery.length; i++) {
		   
		   testString = prefix + trueQuery[i];
		   
		   boolean result = urlVal.isValid(testString);
		   
		   System.out.println("\"" + testString + "\"" + "--	Expected: true;	Actual Result: " + result);
		   
		   testString = "";
	   }
	   
	   //test isValid() with supposedly invalid URL's
	   for (int j = 0; j < falseQuery.length; j++) {
		   
		   testString = prefix + falseQuery[j];
		   
		   boolean result = urlVal.isValid(testString);
		   
		   System.out.println("\"" + testString + "\"" + "--	Expected: false;	Actual Result: " + result);
		   
		   testString = "";
	   }
	   
}


   public void testYourFifthPartition(){
		 //You can use this function to implement your Second Partition testing
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //The second partition tests the PORT validation of isValide().
	   String testString;
	   String prefix = "http://www.google.com";
	   
	   String[] truePort = {"", 
			   				":80", 
			   				":65535", 
			   				":0"};
	   
	   String[] falsePort = {":65536", 
			   					":-1", 
			   					":80a"};
	   
	   
	   System.out.println();
	   System.out.println("-----Fifth Partition: PORT Identifier-----");
	   
	   //test isValid() with supposedly valid URL's
	   for (int i = 0; i < truePort.length; i++) {
		   
		   testString = prefix + truePort[i];
		   
		   boolean result = urlVal.isValid(testString);
		   
		   System.out.println("\"" + testString + "\"" + "--	Expected: true;	Actual Result: " + result);
		   
		   testString = "";
	   }
	   
	   //test isValid() with supposedly invalid URL's
	   for (int j = 0; j < falsePort.length; j++) {
		   
		   testString = prefix + falsePort[j];
		   
		   boolean result = urlVal.isValid(testString);
		   
		   System.out.println("\"" + testString + "\"" + "--	Expected: false;	Actual Result: " + result);
		   
		   testString = "";
	   }
	   
}
   
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
