import java.time.LocalDate;

public class Pascoa {

    LocalDate data;

    Pascoa(int ano) {
        this.data = nextSunday(dateFromYear(ano));
    }

    public int getDia() {
        return this.data.getDayOfMonth();
    }

    public int getMes() {
        return this.data.getMonthValue();
    }

    private LocalDate nextSunday(LocalDate data) {
        int dayOfWeek = data.getDayOfWeek().getValue();
        return data.plusDays(7 - dayOfWeek);
    }

    private LocalDate dateFromYear(int ano) {
        int dia = 0;
        int mes = 0;
        int GoldenNumber = (ano % 19) + 1;
        switch (GoldenNumber) {
            case 1:
                dia = 14;
                mes = 4;
            case 2:
                dia = 3;
                mes = 4;
                break;
            case 3:
                dia = 23;
                mes = 3;
                break;
            case 4:
                dia = 11;
                mes = 4;
                break;
            case 5:
                dia = 31;
                mes = 3;
                break;
            case 6:
                dia = 18;
                mes = 4;
                break;
            case 7:
                dia = 8;
                mes = 4;
                break;
            case 8:
                dia = 28;
                mes = 3;
                break;
            case 9:
                dia = 16;
                mes = 4;
                break;
            case 10:
                dia = 5;
                mes = 4;
                break;
            case 11:
                dia = 25;
                mes = 3;
                break;
            case 12:
                dia = 13;
                mes = 4;
                break;
            case 13:
                dia = 2;
                mes = 4;
                break;
            case 14:
                dia = 22;
                mes = 3;
                break;
            case 15:
                dia = 10;
                mes = 4;
                break;
            case 16:
                dia = 30;
                mes = 3;
                break;
            case 17:
                dia = 17;
                mes = 4;
                break;
            case 18:
                dia = 7;
                mes = 4;
                break;
            case 19:
                dia = 27;
                mes = 3;
                break;
            default:
                dia = LocalDate.now().getDayOfMonth();
                mes = LocalDate.now().getMonthValue();
                break;
        }

        return LocalDate.of(ano, mes, dia);
    }

}