#include <MsTimer2.h>//Библиотека прерываний по таймеру2

unsigned long totalSek = 0;//Здесь мы будем хранить секунды с момента запуска программы
//Этого счетчика хватит на 68 лет :)  (это просто размышления...68 лет нам не нужно)
#define ONE_SECOND 1000
void setup() 
{
Serial.begin(9600);
 MsTimer2::set(ONE_SECOND, to_Timer); // Здесь задаем период 1 секунда
 MsTimer2::start();//Стартуем, теперь таймер запущен
}

void loop() {
//Здесь будет какая-то программа
//у которой теперь есть свой таймер
//и которая не сможет этиму таймеру навредить
}

void to_Timer()//Функция Таймер, он считает и пишет на экран время которое прошло
{
  totalSek++;//Сюда попадаем каждую секунду и приплюсовываем одну секунду
    //Далее рассчитываем часы минуты секунды и записываем на экран
    Serial.println(totalSek);
    Serial.println(totalSek/3600);//Пишем в сериал часы
    Serial.println((totalSek%3600)/60);//Далее минуты
    Serial.println((totalSek%3600)%60);//Далее секунды
    Serial.println(" ");//Делаем разрывчик (совсем необязательно) 

}    