#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <vector>

class TeamTasks {
public:
    /* TeamTasks(std::string Person) {
        TasksInfo forConst;
        forConst[TaskStatus::NEW] = 1;
        forConst[TaskStatus::IN_PROGRESS] = 1;
        forConst[TaskStatus::TESTING] = 2;
        forConst[TaskStatus::DONE] = 3;
        TasksForEveryPerson[Person] = forConst;
    } */
    
  // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
        const TasksInfo& temp_for_return_TasksInfo = TasksForEveryPerson.at(person);
        return temp_for_return_TasksInfo;
    }
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const std::string& person) {
        if (TasksForEveryPerson.count(person)) {  // Если такой разработчик уже есть
            TasksInfo existPersonTaskAdd = TasksForEveryPerson[person];
            existPersonTaskAdd[TaskStatus::NEW]++;
            TasksForEveryPerson[person] = existPersonTaskAdd;
        } else {  // Такого разработчика нет и надо создать его и присвоить ему один статус
            TasksInfo newPersonTaskAdd = TasksForEveryPerson[person];
            newPersonTaskAdd[TaskStatus::NEW] = 1;
            TasksForEveryPerson[person] = newPersonTaskAdd;
        }
    }
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count) {
        TasksInfo updated_tasks;
        TasksInfo untouched_tasks;
        if (TasksForEveryPerson.count(person) == 0) {  // Такого разработчика нет
            std::tuple<TasksInfo, TasksInfo> temp_for_return;
            return temp_for_return;  // Возвращаем кортеж из двух пустых TasksInfo
        }
        TasksInfo concretePerson = TasksForEveryPerson[person];  // Информация статусов задач конкретного разработчика, concretePerson –– map<TaskStatus, int>
        std::vector<int> quantity;
        int sumOfTasksExceptDone = 0;  // Сумма всех задач, кроме выполненных DONE
        int firstNotNullStatus;  // Первый ненулевой статус: 0 - NEW, 1 - IN_PROGRESS, 2 - TESTING, 3 - DONE
        for (int i = 0 ; i < 4; ++i) {
            if (concretePerson[static_cast<TaskStatus>(i)] != 0) {  // Найден не нулевой
                if (i != 3) {  // Статус DONE не считаем
                    sumOfTasksExceptDone += concretePerson.at(static_cast<TaskStatus>(i));
                }
                quantity.push_back(i);
            }
        }
        firstNotNullStatus = quantity[0];
        if (task_count > sumOfTasksExceptDone) {  // Если надо передвинуть больше задач, чем есть невыполненных, то считаем, что надо передвинуть только количество невыполненных
            task_count = sumOfTasksExceptDone;
        }
        if (firstNotNullStatus == 3) {  // Начинать надо c DONE, а это значит, что все задачи выполнены, и сразу возвращаем пару пустых кортежа
            std::tuple<TasksInfo, TasksInfo> twoEmptyTuple;
            return twoEmptyTuple;  // Возвращаем кортеж из двух пустых TasksInfo
        }
        while (task_count != 0) {  // Будем уменьшать task_count на единицу на каждой итерации
            for (int i = firstNotNullStatus; i < 3; ++i) {  // i будет пробегать от первого НЕнулевого статуса до статус TESTING
                while (concretePerson.at(static_cast<TaskStatus>(i)) != 0) {  // Будем уменьшать значение задачи первой НЕнулевой задачи пока оно не станет равно 0
                    if (task_count == 0) {  // Подвинули столько дел, сколько было нужно, теперь выходим
                        goto allFinded;
                    }
                    --concretePerson.at(static_cast<TaskStatus>(i));  // Уменьшили кол-во задач, и теперь должны эту задачу отразить в обновлённых
                    ++updated_tasks[static_cast<TaskStatus>(i + 1)];  // Увеличили значение следующего по порядку статуса на одну задачу
                    --task_count;
                }  // Когда количество первой НЕнулевой задачи станет 0, выходим и переходим к следующему статусу
            }
            
        }
        allFinded:
        untouched_tasks = concretePerson;  // То, что осталось в concretePerson, это и есть нетронутные задачи; переносим их в соотв. словарь
        for (int i = 0; i < 4; ++i) {  // Сумма нетронутных и обновленных задач будет давать все задачи в их новом статусе, нужно их оставить для будущего
            concretePerson[static_cast<TaskStatus>(i)] = untouched_tasks[static_cast<TaskStatus>(i)] + updated_tasks[static_cast<TaskStatus>(i)];
            
            if (concretePerson.at(static_cast<TaskStatus>(i)) == 0) {  // Если в обновленном списке задач есть статус с нулем задач,
                concretePerson.erase(static_cast<TaskStatus>(i));  //  то удаляем
            }
            if (untouched_tasks.at(static_cast<TaskStatus>(i)) == 0) {  // Если в нетронутных есть статус с нулем задач,
                untouched_tasks.erase(static_cast<TaskStatus>(i));  //  то удаляем
            }
            if (updated_tasks.at(static_cast<TaskStatus>(i)) == 0) {  // Если в обновленных есть статус с нулем задач,
                updated_tasks.erase(static_cast<TaskStatus>(i));  //  то удаляем
            }
        }
        untouched_tasks.erase(TaskStatus::DONE);  // DONE задачи не нужно возвращать в нетронутных задачах
        TasksForEveryPerson[person] = concretePerson;  // Записываем обратно для данного человека его обновленный список задач
        return std::make_tuple(updated_tasks, untouched_tasks);
    }
private:
    std::map<std::string, TasksInfo> TasksForEveryPerson;
};