import java.util.Scanner;
public class BMICalculator {							//Creating a class with variables to be filled to be accessed across methods.
	float weight;
	float height;
	String region;
	float BMI;
	String category;

	
Scanner input = new Scanner(System.in);					//Initializing the scanner		
	public static void main(String[] args) {
		BMICalculator app = new BMICalculator();
	    app.readUserData();
	    app.calculateBMI();
	    app.displayBMI();
	}

	public void readUserData() {						//Assigns a string the value obtained from readUnitType
		String unitType = readUnitType();
		readMeasurementData(unitType);					//Passes this string to readMeasurementData
		
		
	}
	private String readUnitType() {						//Checks if the user wants metric or imperial system
		System.out.print("Press M for metric, I for imperial:");
		String unitType = input.next();

		return unitType;
		
	}
	private void readMeasurementData(String unitType) {	//Added my own method setRegion to let me access the imperial or metric signifier for later
		setRegion(unitType);
		
		if(unitType.equals("M")) {						//if statement to filter info where it needs to go
			readMetricData();
		}
		else if (unitType.equals("I")) {
			readImperialData();
		}
		
		
	}
	private void readMetricData() {						//adjusts the vocabulary between metric and imperial
		System.out.print("Enter your weight in kilograms");	//either way they proceed to the same getweight and getheight methods.
		getWeight();
		System.out.print("Enter your height in meters");
		getHeight();
	}
	private void readImperialData() {
		System.out.print("Enter your weight in pounds");
		getWeight();
		System.out.print("Enter your height in inches");
		getHeight();
	}
	public void calculateBMI() {						//calculates the BMI and BMI category in other methods
		getBMI();
		calculateBMICategory();
		
	}
	private void calculateBMICategory() {				//Didn't find a use for this method, pushed it further on
		getBMICategory();
	}
	public void displayBMI() {							//Displays the final calculations and the table to compare
		System.out.printf("Your BMI is %f\n", BMI);
		System.out.printf("Your weight class is %s\n", category);
		System.out.printf("The full list of weight classes are:\n");
		System.out.printf("Underweight: <18.5 BMI\nNormal Weight: >=18.5 and <= 24.9 BMI\n");
		System.out.printf("Overweight: >=25 and <=29.9 BMI\nObese: >=30 BMI");
		
		
	}
	public void getWeight() {							//Takes user input for weight and exits when negative
		
		float weight = input.nextFloat();
		if(weight<0) {
			System.exit(0);
		}
		setWeight(weight);
	}
	private void setWeight(float weight) {				//assigns this weight from getweight to a variable within the class that can be used in the whole program
		
		this.weight=weight;
		
	}
	public void getHeight() {							//same process as getting and setting the weight
		
		float height = input.nextFloat();
		if(height<0) {
			System.exit(0);
		}
		setHeight(height);
		
	}
	private void setHeight(float height) {
		
		this.height=height;
		
	}
	public void getBMI() {								//accesses the region to check which BMI calculation to use and then does it
		float BMI=0;
		if(region.equals("M")) {
			BMI=weight/height;
		}
		else if (region.equals("I")) {
			BMI=((703*weight)/height);
		}
		this.BMI=BMI;
	}
	public void getBMICategory() {						//series of if statements to determine what category they are
		String category="ok";
		if(BMI<18.5) {
			category = "Underweight";
		}
		else if(BMI>=18.5 && BMI<= 24.9) {
			category = "Normal Weight";
		}
		else if(BMI>=25 && BMI <=29.9) {
			category = "Overweight";
		}
		else if(BMI>=30) {
			category = "Obese";
		}
		this.category=category;
	}
	private void setRegion(String unitType) {		//method I added to be able to set the region in its own method
													//I preferred doing it like this because it was similar to how we set the weight and height.
	
		this.region=unitType;
	}
}