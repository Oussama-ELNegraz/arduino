#include <AccelStepper.h>

// Stepers Pins
int Stepper11, Stepper12;
int Stepper21, Stepper22;
int Stepper31, Stepper23;
int Stepper41, Stepper24;

// Define Stepers
AccelStepper stepper1(1,Stepper11,Stepper12);
AccelStepper stepper2(1,Stepper21,Stepper22);
AccelStepper stepper3(1,Stepper31,Stepper23);
AccelStepper stepper4(1,Stepper41,Stepper24);

/*
// Define Data
int theta1,theta2,theta3,z;
*/

// Define Factors
int theta1ToStep,theta2ToStep,theta3ToStep,zToStep;



// Define Array of Data
String data[20];
/*
  Data :  [0] => theta1
          [1] => theta2
          [2] => theta3
          [3] => z  
          [4] => speed
          [5] => acceleration   
          [6] => Run Status      
          [7] => theta1Pos // Pos1,pos2,pos3,posN
          [8] => theta2Pos // Pos1,pos2,pos3,posN
          [9] => theta2Pos // Pos1,pos2,pos3,posN
          [10]=> zPos      // Pos1,pos2,pos3,posN


data[0];data[1];data[2];data[3];data[4];data[5];data[6]
                     
*/

// Define Current Position
int Step1Pos,Step2Pos,Step3Pos,Step4Pos;


// Define Max Speed And Acceleration
int maxSpeed,Acceleration;



// Define Array Data 
int theta1[],theta2[],theta3[],z[];



/*

Inverse Kinematics OR Run Automaticaly Position

x  ,y => theta 1 , theta 2 , theta 3



Array Tableau 
  Index       theta1        theta2        theta3        z
  1             12            12             45         45 
  2             12            12             45         12
  3             12            12             45         41
  4             12            12             45         13
  5             12            12             45         14


Loop 1 à NumberOfElement



*/







void setup() {
  Serial.begin(9600);  

  // Stepper Initilize Speed and Acceleration
  stepper1.setMaxSpeed(maxSpeed);
  stepper1.setAcceleration(Acceleration);
  stepper2.setMaxSpeed(maxSpeed);
  stepper2.setAcceleration(Acceleration);
  stepper3.setMaxSpeed(maxSpeed);
  stepper3.setAcceleration(Acceleration);
  stepper4.setMaxSpeed(maxSpeed);
  stepper4.setAcceleration(Acceleration);

  
}

void loop() {
        if(Serial.available()){    

              // Set speed And Acceleration
              
              stepper1.setSpeed(data[4]);
              stepper2.setSpeed(data[4]);
              stepper3.setSpeed(data[4]);
              stepper4.setSpeed(data[4]);
      
              stepper1.setAcceleration(data[5]);
              stepper2.setAcceleration(data[5]);
              stepper3.setAcceleration(data[5]);
              stepper4.setAcceleration(data[5]);


                          
          // Automatique Position           
          /*[6] => Run Status      
            [7] => theta1Pos // Pos1,pos2,pos3,posN
            [8] => theta2Pos // Pos1,pos2,pos3,posN
            [9] => theta2Pos // Pos1,pos2,pos3,posN
            [10]=> zPos      // Pos1,pos2,pos3,posN
          */
        if(data[6] == 1){
            int i = 0;
            while(data[7].length() > 0){

                // Extract the data
                  int index = data[7].indexOf(","); 
                  theta1[i] = atol(data[7].substring(0, index).c_str()); 
                  data[7]   = data[7].substring(index + 1); 

                  // string.substring(Start,End);
          
                  index     = data[8].indexOf(",");
                  theta2[i] = atol(data[8].substring(0, index).c_str());
                  data[8]   = data[8].substring(index + 1); 

                  index     = data[9].indexOf(",");
                  theta3[i] = atol(data[9].substring(0, index).c_str());
                  data[9]   = data[9].substring(index + 1); 

                  index     = data[10].indexOf(",");
                  z[i]      = atol(data[10].substring(0, index).c_str()); 
                  data[10]  = data[10].substring(index + 1);                   
                  
                  i++;             
            }
            for(int j = 0 ;j < i ; j++){
                            
                        Step1Pos = theta1[j] * theta1AngleToSteps;
                        Step2Pos = theta2[j] * theta1ToStep;                      
                        Step3Pos = theta3[j] * theta1ToStep;
                        Step4Pos = z[j]      * zToStep;
            
                        stepper1.moveTo(stepper1Position);
                        stepper2.moveTo(stepper2Position);
                        stepper3.moveTo(stepper3Position);
                        stepper4.moveTo(stepper4Position);
                      
                        while (stepper1.currentPosition() != Step1Pos || stepper2.currentPosition() != Step2Pos ||
                               stepper3.currentPosition() != Step3Pos || stepper4.currentPosition() != Step4Pos) {
                          stepper1.run();
                          stepper2.run();
                          stepper3.run();
                          stepper4.run();
                          
                        }
                        
              }
        }else{
            // Forward Kinematics
    
            Step1Pos = data[0] * theta1AngleToSteps;
            Step2Pos = Data[1] * theta1ToStep;                      
            Step3Pos = Data[2] * theta1ToStep;
            Step4Pos = Data[3] * zToStep;
            
            stepper1.moveTo(stepper1Position);
            stepper2.moveTo(stepper2Position);
            stepper3.moveTo(stepper3Position);
            stepper4.moveTo(stepper4Position);
          
            while (stepper1.currentPosition() != Step1Pos || stepper2.currentPosition() != Step2Pos ||
                   stepper3.currentPosition() != Step3Pos || stepper4.currentPosition() != Step4Pos) {
              stepper1.run();
              stepper2.run();
              stepper3.run();
              stepper4.run();
              
            }
            
        }



        





   }
}
