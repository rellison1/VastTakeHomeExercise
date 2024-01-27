# VastTakeHomeExercise
# Author: Reed Ellison
# Date: 26 January 2024

# Purpose: This repository is used for the submission of an implemented project according to the provided problem set and instructions in the following instructions which were provided by VAST as a part of the interview process for a position at the company.

Vast Take-Home Coding Exercise
Problem Set:
You are tasked with developing software to manage a space mining operation that extracts Helium-3 from
lunar regolith. The operation consists of n-mining stations, each capable of handling one mining truck at a
time. Mining trucks spend varying amounts of time mining, ranging from one to five hours. For the sake of
this exercise, each truck has a random probability of mining in that range, per load. Mining trucks require
30 minutes to transition to an available mining station. Unloading a mining truck takes 5 minutes. Mining
trucks should be directed to the first open station or if all stations are occupied, the station with the shortest
queue. Trucks do not move queues after they enter them.
Your objective is to create a simulation that can accept a configurable number of mining trucks and stations
and then calculate statistics for each mining station and mining truck. The simulation should run faster than
real-time. The simulation should represent 72 hours of continuous mining.
Language and programming paradigms:
Please implement this project in C++. Please leverage OOP where it is appropriate.
How to Submit:
Submit your code and any accompanying content, such as data or results, using GitHub or Bitbucket.
Please email us a link to your submitted code when you are ready for us to review it.
Goal:
The primary goal of this challenge is to demonstrate your professionalism as a software engineer. This
process is designed to mimic a real-world scenario, including design, implementation, and design review.
You will be evaluated based on various skills, including:
1. Communication: Clear and concise explanations of your code and design.
2. Documentation: Providing well-documented code and explanations.
3. Code Cleanliness: Writing clean and organized code.
4. Code Deployment: Demonstrating your ability to deploy and manage code.
5. Testing: Implementing appropriate testing strategies.
Questions:
Please feel free to ask any clarifying questions about this assignment via email.

# Notes/Documentation of the creation and working of the project:

  # General Details
    The project was written with the Visual Studios IDE and was uploaded to Github through the integrated functionality provided in Visual Studios.

  # Initial Analysis/Commentary on the prompt
    The prompt/problem set is rather straightforward although there are no implementation specifics (besides using C++) and some details on requirements/ouptut are not specified. Despite this lack of certain details, I did not ask any questions due to a couple of reasons: 1) The assignment was due within a week so time was not on my side to ask clarifying questions via email. 2) The instructions did indicate output/requirements(although not very specific and detailed output related specifics) which the project does meet so clarification did not seem essential. Given the ability and need to further clarify, which I most definitely would in any work related task, I would most definitely have reached out and ensured additional details/requirements were provided as much as possible. 

    The prompt's ask is to be able to simulate a mining operation where there are a variable number of trucks and stations. The trucks mine at stations and consequently unload and then move to or queue at another station. The actions of the trucks, like moving, take a certain amount of time and are specified in the instructions. Given this information, my first thought and breakdown of this scenario is that the objects/components of this program would be the trucks, stations, and the managing operation which would need to coordinate/house the variable trucks and stations. Simply, the operation would need to create and hold a number of trucks and do the same for the stations and manage the interactions between the trucks and stations. The trucks would follow a pattern or state machine behavior. The trucks would behave as such: (Moving to station) -> (Queue at station if station had another truck at it) -> (Mine once it could enter the station) -> (Unload) -> (Move to next station) -> ..... and so on. The stations would more simply need to acknowledge when a truck is present at it and then hold/provide a queue that trucks could wait in. Due to additional specifications in the prompt, the operation needs to direct the trucks, when they are available, to the most open(least occupied) station. This requires operation keeping track of which station is the choice for a truck to go to. The stations are not directly dependent on the time but simply are affected by the trucks. The trucks are both state and time dependent. The operation must manage the relationship/status between the two throughout the duration of the simulation.

  # Design
    The design tries to mimic my take on the prompt which is matching classes to the objects or components of the program. The interdepencies/interactions are managed by the Operation which contains containers of the trucks and the stations. The simulation proceeds by performing an 'update' every minute of the duration of the simulation. This follows the logic of a simulation where we try to simulate real time scenario. An update is performed every minute as it is the lowest time unit that will ensure all actions are handled on time. For instance, if we checked/updated every hour, the unloading which takes 5 minutes would not be caught. A minute is chosen as the mining duration can be any range of minutes from 1 hour to 5 hours so every minute needs to be checked. The trucks are checked first to see when, based on the times of the actions and when they were started, if the state should change. The stations basically react or will change based on what the trucks are doing. 

  # Considerations taken when writing the code
    Extensibility
      I tried to balance making the design more flexible/open/extensible but given the prompt and no need for enhancements (given it is a one off project) the design could be done to be more flexble if there was the expectation of updating/expanding.
    Namespaces
      I went against using a namespace due to scope of this project. Given a larger scoped effort, I would have most likely used namespaces to prevent conflicting names.
    Comments
      The attempt is always to have the code meaning be obvious with variable names and clear code. Where the reason for some code is not inherently obvious, comments should be used to explain why. Attempt was to not be redundant with the code (being explicit) and the comments.
    Tests
      The tests are setup to test the whole run simulation. Unit tests could be added to test individual parts but with the current design and the problem set being time(state) based, I went with checking the entire simulation run as there are alot of checks to do in every simulation run and these checks would be applicable to every run of the program/operation.
    Additional considerations
      Other considerations were taken and can be discussed when reviewing the code changes.
    



