char input,num;
int buff[5];
int j=-1;
String mensagem;

void setup()
{
    Serial.begin(9600);
}
 

void loop()
{
    if(Serial.available()>0)
    {
        input=Serial.read();
        mensagem = input;
            
         Serial.print(mensagem);
        }
    }
