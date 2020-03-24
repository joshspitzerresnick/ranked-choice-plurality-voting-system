/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

#include <iostream>
#include <string>

/**
 * @brief The main class for passengers.
 *
 * Is a passenger.
 */
class Passenger {  // : public Reporter {
 public:
  /**
  * @brief Constructs a passenger with a standard name and id.
  *
  *
  * @param[in] int holding an id number
  * @param[in] string holding a name of a created passenger.
  *
  */
  explicit Passenger(int = -1, std::string = "Nobody");
  /**
  * @brief Updates a passenger.
  */
  void Update();
  /**
  * @brief Updates time_on_bus_ to reflect getting on a bus.
  */
  void GetOnBus();
  /**
  * @brief Returns total time waited at stop and on bus.
  *
  * @return int holding total wait in time steps.
  */
  int GetTotalWait() const;
  /**
  * @brief Returns whether or not passenger is on a bus.
  *
  * @return bool holding whether or not passenger is on a bus.
  */
  bool IsOnBus() const;
  /**
  * @brief Returns destination_stop_id_.
  *
  * @return int holding destination_stop_id_.
  */
  int GetDestination() const;
  /**
  * @brief Reports status to std::cout.
  */
  void Report() const;
  /**
  * @brief Reports status to ostream object.
  *
  * @param[in] std::ostream& holding ostream object to report to.
  */
  void Report(std::ostream &  out) const;

 private:
  std::string name_;
  int destination_stop_id_;
  int wait_at_stop_;
  int time_on_bus_;
  int id_;
  static int count_;   // global count, used to set ID for new instances
};
#endif  // SRC_PASSENGER_H_
