#include <functional>
#include <iostream>
using namespace std;

template <typename Type>
class Array {
 private:
  Type *data;
  int count;
  int partition(int start, int end, function<int(Type, Type)> f) {
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++) {
      if (f(this->data[j], this->data[end]) < 0) {
        i++;
        this->swap(i, j);
      }
    }
    this->swap(i + 1, end);
    return (i + 1);
  }
  void quickSort(int start, int end, function<int(Type, Type)> f) {
    if (start < end) {
      int pivotIndex = this->partition(start, end, f);

      this->quickSort(start, pivotIndex - 1, f);
      this->quickSort(pivotIndex + 1, end, f);
    }
  }

 public:
  ~Array() { delete[] this->data; }
  Array<Type>() {
    this->data = new Type[0];
    this->count = 0;
  }
  Array<Type>(const Array<Type> &obj) {
    this->count = obj.count;
    this->data = new Type[count];
    for (int i = 0; i < count; i++) {
      this->data[i] = obj.data[i];
    }
  }
  Array<Type>(Type *data, int count) {
    this->data = new Type[count];
    for (int i = 0; i < count; i++) {
      this->data[i] = data[i];
    }
    this->count = count;
  }
  Type *getData() { return this->data; }
  int getCount() { return this->count; }
  void copy(Type *dest) {
    for (int i = 0; i < count; i++) {
      dest[i] = this->data[i];
    }
  }
  Array<Type> clone() {
    Type *outArr = new Type[count];
    this->copy(outArr);
    return Array<Type>(outArr, count);
  }
  Array<Type> *push(Type element) {
    int newCount = count + 1;
    Type *outArr = new Type[newCount];
    if (!this->count || this->count != 0) {
      this->copy(outArr);
      delete[] this->data;
    }
    outArr[count] = element;
    this->data = outArr;
    this->count++;
    return this;
  }
  Array<Type> *pop() {
    if (count <= 0) {
      return this;
    }
    int newCount = count - 1;
    Type *outArr = new Type[newCount];
    for (int i = 0; i < newCount; i++) {
      outArr[i] = this->data[i];
    }
    delete[] this->data;
    this->count = newCount;
    this->data = outArr;
    return this;
  }
  Array<Type> *filter(function<bool(Type)> f) {
    Array<Type> *out = new Array<Type>();
    for (int i = 0; i < count; i++) {
      if (f(this->data[i])) {
        out->push(this->data[i]);
      }
    }
    delete[] this->data;
    this->count = out->count;
    this->data = new Type[out->getCount()];
    out->copy(this->data);
    delete out;
    return this;
  }
  void forEach(function<void(Type)> f) {
    if (!this->count || this->count == 0) return;
    for (int i = 0; i < this->count; i++) {
      f(this->data[i]);
    }
  }
  void swap(int indexA, int indexB) {
    Type *a = &this->data[indexA];
    Type *b = &this->data[indexB];
    Type t = *a;
    *a = *b;
    *b = t;
  }
  void sort(function<int(Type, Type)> f) {
    if (!this->count || this->count == 0) return;
    this->quickSort(0, this->getCount() - 1, f);
  }
  template <typename MapType>
  Array<MapType> *map(function<MapType(Type)> f) {
    MapType *outArr = new MapType[this->count];
    Array<MapType> *out = new Array<MapType>(outArr, this->count);
    for (int i = 0; i < this->count; i++) {
      out->getData()[i] = f(this->data[i]);
    }
    return out;
  }
  template <typename ReduceType>
  ReduceType reduce(
      function<ReduceType(ReduceType accumulator, Type currentValue,
                          int currentIndex = NULL, Type *srcArray) = NULL>
          f,
      ReduceType initValue) {
    ReduceType value = initValue;
    for (int i = 0; i < this->count; i++) {
      value = f(value, this->data[i], i, this->data);
    }
    return value;
  }
  Array<Type> concat(Array<Type> array) {
    Array<Type> temp = this->clone();
    array.forEach([=](Type element) { temp.push(element); });
    return temp;
  }
  Array<Type> reverse() {
    Array<Type> temp = this->clone();
    for (int i = 0; i < temp.getCount() / 2; i++) {
      temp.swap(i, temp.getCount() - i - 1);
    }
    return temp;
  }
};

class Config {
 public:
  static const int MARS_DAY_HOURS = 25;
  static const int MISSION_FORMULATION_WEIGHT = 25;
  static const int MISSION_DURATION_WEIGHT = 25;
  static const int MISSION_DISTANCE_WEIGHT = 25;
};

enum MissionType {
  EMERGENCY,
  POLAR,
  MOUNTAINOUS,
};

enum MissionStatus {
  IDLE,
  IN_PROGRESS,
  COMPLETED,
  CANCELED,
  FAILED,
  COUNT,
};

class Mission {
 private:
  // Mission id: unique identifier for a mission
  int id;
  // Mission type: emergency, polar or mountainous
  MissionType missionType;
  // Mission status: idle, in progress, completed or failed
  MissionStatus missionStatus;
  // Formulation day: starts from day zero (start of the program)
  int formulationDay;
  // Distance of the mission from the base in kilometers
  int distance;
  // Duration (independent of rover speed) for the completion of the mission in
  // mars days
  int duration;
  // Mission's significance (a positive integer the higher the higher the
  // significance)
  int significance;
  // Mission's assigned rover
  Rover *rover;

 public:
  Mission(int id, MissionType missionType, int formulationDay, int distance,
          int duration, int significance) {
    this->id = id;
    this->missionType = missionType;
    this->formulationDay = formulationDay;
    this->distance = distance;
    this->duration = duration;
    this->significance = significance;
  }
  int getMissionId() { return this->id; }
  MissionType getMissionType() { return this->missionType; }
  void setMissionType(MissionType missionType) {
    this->missionType = missionType;
  }
  MissionStatus getMissionStatus() { return this->missionStatus; }
  void setMissionStatus(MissionStatus missionStatus) {
    this->missionStatus = missionStatus;
  }
  int getFormulationDay() { return this->formulationDay; }
  int getDistance() { return this->distance; }
  int getSignificance() { return this->significance; }
  int getDuration() { return this->duration; }
  int getMissionPriority(int currentDay) {
    int daysSinceFormulation = this->formulationDay - currentDay;
    return (Config::MISSION_FORMULATION_WEIGHT * daysSinceFormulation +
            Config::MISSION_DURATION_WEIGHT * this->duration +
            Config::MISSION_DISTANCE_WEIGHT * this->distance) *
           this->significance;
  }
  void setRover(Rover *rover) { this->rover = rover; }
  Rover *getRover() { return this->rover; }
};

enum RoverTypes {
  EMERGENCY,
  POLAR,
  MOUNTAINOUS,
  COUNT,
};

enum RoverStatus {
  IDLE,
  IN_CHECKUP,
  IN_MAINTENANCE,
  HALF_CAPACITY,
  ON_MISSION,
};

class Rover {
 private:
  RoverTypes roverType;
  RoverStatus roverStatus;
  int checkupInterval;
  int checkupDuration;
  int speed;
  int autoPromote;
  Mission *currentMission;

  int id;

 public:
  static int roverCount;
  Rover(RoverTypes roverType, int checkupInterval, int checkupDuration,
        int speed, int autoPromote) {
    this->roverType = roverType;
    this->checkupInterval = checkupInterval;
    this->checkupDuration = checkupDuration;
    this->speed = speed;
    this->autoPromote = autoPromote;
    this->id = roverCount;
    Rover::roverCount++;
  }
  void setCurrentMission(Mission *currentMission) {
    this->currentMission = currentMission;
  }
  int getRoverId() { return this->id; }
  Mission *getCurrentMission() { return this->currentMission; }
  RoverTypes getRoverType() { return this->roverType; }
  RoverStatus getRoverStatus() { return this->roverStatus; }
  void reportToStation() {

  }
};
int Rover::roverCount = 0;

class RoverStation {
 private:
  MarsStation *parentStation;
  Array<Rover *> rovers;

 public:
  RoverStation(MarsStation *parentStation) {
    this->parentStation = parentStation;
  }
  Array<Rover *> getRovers() { return this->rovers; }
  Array<Rover *> *getRoversByType(RoverTypes roverType) {
    return this->rovers.clone().filter(
        [=](Rover *rover) { return rover->getRoverType() == roverType; });
  }
  Array<Rover *> *getRoversByStatus(RoverStatus roverStatus) {
    return this->rovers.clone().filter(
        [=](Rover *rover) { return rover->getRoverStatus() == roverStatus; });
  }
  Rover *getRoverById(int roverId) {
    auto rovers = this->rovers.clone().filter(
        [=](Rover *rover) { return rover->getRoverId() == roverId; });
    if (rovers->getCount() > 0) {
      return rovers->getData()[0];
    }
    return nullptr;
  }
  Array<Rover *> *getRoversByTypeAndStatus(RoverTypes roverType,
                                           RoverStatus roverStatus) {
    return this->rovers.clone().filter([=](Rover *rover) {
      return rover->getRoverType() == roverType &&
             rover->getRoverStatus() == roverStatus;
    });
  }
};

enum EventTypes {
  ADD_ROVERS,
  ADD_MISSION,
  CANCEL_MISSION,
  PROMOTE_MISSION,
};

class Event {
 public:
  int id;
  int formulationDay;
  Event(int id, int formulationDay) {
    this->id = id;
    this->formulationDay = formulationDay;
  }
  int getId() { return this->id; }
  int getFormulationDay() { return this->formulationDay; }
  virtual void execute(MarsStation *marsStation) = 0;
};

class AddRoverEvent : public Event {
 private:
  RoverTypes roverType;
  int checkupInterval;
  int checkupDuration;
  int speed;
  int autoPromote;

 public:
  AddRoverEvent(int id, int formulationDay, RoverTypes roverType,
                int checkupInterval, int checkupDuration, int speed,
                int autoPromote)
      : Event(id, formulationDay) {
    this->roverType = roverType;
    this->checkupInterval = checkupInterval;
    this->checkupDuration = checkupDuration;
    this->speed = speed;
    this->autoPromote = autoPromote;
  }
  void execute(MarsStation *marsStation) {
    marsStation->getRoverStation()->getRovers().push(new Rover(
        roverType, checkupInterval, checkupDuration, speed, autoPromote));
  }
};

class AddMissionEvent : public Event {
 private:
  MissionType missionType;
  int distance;
  int duration;
  int significance;

 public:
  AddMissionEvent(int id, int formulationDay, MissionType missionType,
                  int distance, int duration, int significance)
      : Event(id, formulationDay) {
    this->missionType = missionType;
    this->distance = distance;
    this->duration = duration;
    this->significance = significance;
  }
  void execute(MarsStation *marsStation) {
    marsStation->getHeadQuarters()->getMissions()->push(
        new Mission(this->id, this->missionType, this->formulationDay,
                    this->distance, this->duration, this->significance));
  }
};

class CancelMissionEvent : public Event {
 private:
  int missionId;

 public:
  CancelMissionEvent(int id, int formulationDay, int missionId)
      : Event(id, formulationDay) {
    this->missionId = missionId;
  }
  void execute(MarsStation *marsStation) {
    Mission *mission =
        marsStation->getHeadQuarters()->getMissionById(this->missionId);
    if (mission) {
      auto status = mission->getMissionStatus();
      if (status == MissionStatus::IDLE) {
        mission->setMissionStatus(MissionStatus::CANCELED);
      } else if (status == MissionStatus::IN_PROGRESS) {
        mission->getRover()->reportToStation();
        mission->setMissionStatus(MissionStatus::CANCELED);
      }
    }
  }
};

class PromoteMissionEvent : public Event {
  private:
  int missionId;

 public:
  PromoteMissionEvent(int id, int formulationDay, int missionId)
      : Event(id, formulationDay) {
    this->missionId = missionId;
  }
  void execute(MarsStation *marsStation) {
    Mission *mission =
        marsStation->getHeadQuarters()->getMissionById(this->missionId);
    if (mission) {
      auto status = mission->getMissionStatus();
      auto type = mission->getMissionType();
      if (status == MissionStatus::IDLE && type == MissionType::MOUNTAINOUS) {
        mission->setMissionType(MissionType::EMERGENCY);
      }
    }
  }
};

class HeadQuarters {
 private:
  MarsStation *parentStation;
  Array<Mission *> missions;

 public:
  HeadQuarters(MarsStation *parentStation) {
    this->parentStation = parentStation;
  }
  Array<Mission *> *getMissions() { return &this->missions; }
  Mission *getMissionById(int missionId) {
    auto missions = this->missions.clone().filter(
        [=](Mission *mission) { return mission->getMissionId() == missionId; });
    if (missions->getCount() > 0) {
      return missions->getData()[0];
    }
    return nullptr;
  }
  Array<Mission *> *getMissionsByType(MissionType missionType) {
    return this->missions.clone().filter([=](Mission *mission) {
      return mission->getMissionType() == missionType;
    });
  }
  Array<Mission *> *getMissionsByStatus(MissionStatus missionStatus) {
    return this->missions.clone().filter([=](Mission *mission) {
      return mission->getMissionStatus() == missionStatus;
    });
  }
  Array<Mission *> *getMissionsByTypeAndStatus(MissionType missionType,
                                               MissionStatus missionStatus) {
    return this->missions.clone().filter([=](Mission *mission) {
      return mission->getMissionType() == missionType &&
             mission->getMissionStatus() == missionStatus;
    });
  }
};

class MarsStation {
 private:
  int currentDay = 0;
  RoverStation roverStation = RoverStation(this);
  HeadQuarters headQuarters = HeadQuarters(this);

 public:
  RoverStation *getRoverStation() { return &this->roverStation; }
  HeadQuarters *getHeadQuarters() { return &this->headQuarters; }
  bool processDay() {
    this->currentDay++;
    return true;
  }
};

int main() {
  MarsStation marsStation;
  while (1) {
    if (!marsStation.processDay()) {
      break;
    }
  }
}