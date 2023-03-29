import java.util.ArrayList;
import java.util.List;

public class SantaScenario {
	public Santa santa;
	public List<Elf> elves;
	//public List<Reindeer> reindeers;
	public boolean isDecember;
	
	public static void main(String args[]) throws InterruptedException {
		SantaScenario scenario = new SantaScenario();
		scenario.isDecember = false;
		// create the participants
		// Santa
		scenario.santa = new Santa(scenario);
		Thread th = new Thread(scenario.santa);
		th.start();
		// The elves: in this case: 10
		scenario.elves = new ArrayList<>();
		for(int i = 0; i != 10; i++) {
			Elf elf = new Elf(i+1, scenario);
			scenario.elves.add(elf);
			th = new Thread(elf);
			th.start();
		}
		// The reindeer: in this case: 9
		/*
		 THERE ARE NO REINDEER DURING STEP 2
		 
		scenario.reindeers = new ArrayList<>();
		for(int i=0; i != 9; i++) {
			Reindeer reindeer = new Reindeer(i+1, scenario);
			scenario.reindeers.add(reindeer);
			th = new Thread(reindeer);
			th.start();
		}
		*/
		// now, start the passing of time
		for(int day = 1; day < 500; day++) {
			// wait a day
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			// turn on December
			if (day > (365 - 31)) {
				scenario.isDecember = true;
			}
			
			// stop the threads using deferred termination once the day reaches 370.
			if (day == 370) {
				for(Elf elf: scenario.elves) {
					elf.checkThread = false;
				}
				/*
				 * THERE ARE NO REINDEER DURING STEP 2
				for(Reindeer reindeer: scenario.reindeers) {
					reindeer.checkThread = false;
				}
				*/
				scenario.santa.checkThread = false;
			}
			
			
			
			// print out the state:
			System.out.println("***********  Day " + day + " *************************");
			scenario.santa.report();
			for(Elf elf: scenario.elves) {
				elf.report();
			}
			/*
			 * THERE ARE NO REINDEER DURING STEP 2
			for(Reindeer reindeer: scenario.reindeers) {
				reindeer.report();
			}
			*/
		}
	}
	
	
	
}
