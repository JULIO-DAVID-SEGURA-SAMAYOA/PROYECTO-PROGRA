#include "MySQLConexion.h"
#include "EloquentORM.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

using namespace std;



class UsuarioSistema {
    MySQLConexion& conn;
    EloquentORM orm;
public:
    UsuarioSistema(MySQLConexion& conexion)
        : conn(conexion), orm(conexion, "usuarios_sistema", {"nombre_usuario", "contrasena"}) {}

    void crear() {
        EloquentORM usuario(conn, "usuarios_sistema", {"nombre_usuario", "contrasena"});
        string nombre_usuario, contrasena;

        cout << "Nombre de usuario: "; cin >> nombre_usuario;
        cout << "Contraseña: "; cin >> contrasena;

        usuario.set("nombre_usuario", nombre_usuario);
        usuario.set("contrasena", contrasena);

        cout << (usuario.create() ? "Usuario creado correctamente.\n" : "Error al crear usuario.\n");
    }

    void leer() {
        auto lista = orm.getAll();
        for (auto& reg : lista) {
            cout << "ID: " << reg["id"]
                 << ", Usuario: " << reg["nombre_usuario"] << endl;
        }
        cout << "Presiona Enter para continuar..." << endl;
        cin.ignore(); cin.get();
    }

    void actualizar() {
        EloquentORM usuario(conn, "usuarios_sistema", {"id", "nombre_usuario", "contrasena"});
        int id;
        string nombre_usuario, contrasena;

        cout << "ID del usuario a actualizar: "; cin >> id;
        cout << "Nuevo nombre de usuario: "; cin >> nombre_usuario;
        cout << "Nueva contraseña: "; cin >> contrasena;

        usuario.set("id", to_string(id));
        usuario.set("nombre_usuario", nombre_usuario);
        usuario.set("contrasena", contrasena);

        cout << (usuario.update() ? "Usuario actualizado correctamente.\n" : "Error al actualizar usuario.\n");
    }

    void eliminar() {
        EloquentORM usuario(conn, "usuarios_sistema", {"nombre_usuario"});
        int id;
        cout << "ID del usuario a eliminar: "; cin >> id;

        if (usuario.find(id)) {
            cout << "Se eliminó el usuario: " << usuario.get("nombre_usuario") << endl;
            usuario.remove();
        } else {
            cout << "No se encontró usuario con ese ID.\n";
        }
    }
};

class Reserva {
    MySQLConexion& conn;
    EloquentORM orm;
public:
    Reserva(MySQLConexion& conexion)
        : conn(conexion), orm(conexion, "reservas", {"id_vuelo", "id_pasajero", "codigo_reserva", "numero_boleto", "asiento"}) {}

    void crear() {
        EloquentORM reserva(conn, "reservas", {"id_vuelo", "id_pasajero", "codigo_reserva", "numero_boleto", "asiento"});
        int id_vuelo, id_pasajero;
        string codigo_reserva, numero_boleto, asiento;

        cout << "ID del vuelo: "; cin >> id_vuelo;
        cout << "ID del pasajero: "; cin >> id_pasajero;
        cout << "Codigo de reserva: "; cin >> codigo_reserva;
        cout << "Numero de boleto: "; cin >> numero_boleto;
        cout << "Asiento asignado (ej. 5A): "; cin >> asiento;

        reserva.set("id_vuelo", to_string(id_vuelo));
        reserva.set("id_pasajero", to_string(id_pasajero));
        reserva.set("codigo_reserva", codigo_reserva);
        reserva.set("numero_boleto", numero_boleto);
        reserva.set("asiento", asiento);

        cout << (reserva.create() ? "Reserva creada exitosamente.\n" : "Error al crear reserva.\n");
    }

    void leer() {
        auto lista = orm.getAll();
        for (auto& reg : lista) {
            cout << "ID: " << reg["id"]
                 << ", ID Vuelo: " << reg["id_vuelo"]
                 << ", ID Pasajero: " << reg["id_pasajero"]
                 << ", Codigo Reserva: " << reg["codigo_reserva"]
                 << ", No. Boleto: " << reg["numero_boleto"]
                 << ", Asiento: " << reg["asiento"] << endl;
        }
        cout << "Presiona Enter para continuar..." << endl;
        cin.ignore(); cin.get();
    }

    void actualizar() {
        EloquentORM reserva(conn, "reservas", {"id", "id_vuelo", "id_pasajero", "codigo_reserva", "numero_boleto", "asiento"});
        int id, id_vuelo, id_pasajero;
        string codigo_reserva, numero_boleto, asiento;

        cout << "ID de la reserva a actualizar: "; cin >> id;
        cout << "Nuevo ID vuelo: "; cin >> id_vuelo;
        cout << "Nuevo ID pasajero: "; cin >> id_pasajero;
        cout << "Nuevo codigo de reserva: "; cin >> codigo_reserva;
        cout << "Nuevo numero de boleto: "; cin >> numero_boleto;
        cout << "Nuevo asiento: "; cin >> asiento;

        reserva.set("id", to_string(id));
        reserva.set("id_vuelo", to_string(id_vuelo));
        reserva.set("id_pasajero", to_string(id_pasajero));
        reserva.set("codigo_reserva", codigo_reserva);
        reserva.set("numero_boleto", numero_boleto);
        reserva.set("asiento", asiento);

        cout << (reserva.update() ? "Reserva actualizada correctamente.\n" : "Error al actualizar reserva.\n");
    }

    void eliminar() {
        EloquentORM reserva(conn, "reservas", {"codigo_reserva"});
        int id;
        cout << "ID de la reserva a eliminar: "; cin >> id;

        if (reserva.find(id)) {
            cout << "Se eliminó la reserva con código: " << reserva.get("codigo_reserva") << endl;
            reserva.remove();
        } else {
            cout << "No se encontró reserva con ese ID.\n";
        }
    }
};

class Pasajero {
    MySQLConexion& conn;
    EloquentORM orm;
public:
    Pasajero(MySQLConexion& conexion)
        : conn(conexion), orm(conexion, "pasajeros", {"nombre", "apellido", "email"}) {}

    void crear() {
        EloquentORM pasajero(conn, "pasajeros", {"nombre", "apellido", "email"});
        string nombre, apellido, email;

        cout << "Nombre del pasajero: "; cin >> nombre;
        cout << "Apellido: "; cin >> apellido;
        cout << "Email: "; cin >> email;

        pasajero.set("nombre", nombre);
        pasajero.set("apellido", apellido);
        pasajero.set("email", email);

        cout << (pasajero.create() ? "Pasajero creado exitosamente.\n" : "Error al crear pasajero.\n");
    }

    void leer() {
        auto lista = orm.getAll();
        for (auto& reg : lista) {
            cout << "ID: " << reg["id"]
                 << ", Nombre: " << reg["nombre"]
                 << ", Apellido: " << reg["apellido"]
                 << ", Email: " << reg["email"] << endl;
        }
        cout << "Presiona Enter para continuar..." << endl;
        cin.ignore(); cin.get();
    }

    void actualizar() {
        EloquentORM pasajero(conn, "pasajeros", {"id", "nombre", "apellido", "email"});
        int id;
        string nombre, apellido, email;

        cout << "ID del pasajero a actualizar: "; cin >> id;
        cout << "Nuevo nombre: "; cin >> nombre;
        cout << "Nuevo apellido: "; cin >> apellido;
        cout << "Nuevo email: "; cin >> email;

        pasajero.set("id", to_string(id));
        pasajero.set("nombre", nombre);
        pasajero.set("apellido", apellido);
        pasajero.set("email", email);

        cout << (pasajero.update() ? "Pasajero actualizado correctamente.\n" : "Error al actualizar pasajero.\n");
    }

    void eliminar() {
        EloquentORM pasajero(conn, "pasajeros", {"nombre", "apellido"});
        int id;
        cout << "ID del pasajero a eliminar: "; cin >> id;

        if (pasajero.find(id)) {
            cout << "Se eliminó al pasajero: " << pasajero.get("nombre") << " " << pasajero.get("apellido") << endl;
            pasajero.remove();
        } else {
            cout << "No se encontró pasajero con ese ID.\n";
        }
    }
};

class Vuelo {
    MySQLConexion& conn;
    EloquentORM orm;
public:
    Vuelo(MySQLConexion& conexion)
        : conn(conexion), orm(conexion, "vuelos", {"codigo_vuelo", "id_origen", "id_destino", "fecha", "hora_abordaje", "hora_salida", "hora_llegada", "aerolinea"}) {}

    void crear() {
        EloquentORM vuelo(conn, "vuelos", {"codigo_vuelo", "id_origen", "id_destino", "fecha", "hora_abordaje", "hora_salida", "hora_llegada", "aerolinea"});
        string codigo, fecha, abordaje, salida, llegada, aerolinea;
        int origen, destino;

        cout << "Codigo de vuelo (ej. 5U141): "; cin >> codigo;
        cout << "ID aeropuerto de origen: "; cin >> origen;
        cout << "ID aeropuerto de destino: "; cin >> destino;
        cout << "Fecha del vuelo (YYYY-MM-DD): "; cin >> fecha;
        cout << "Hora de abordaje (HH:MM): "; cin >> abordaje;
        cout << "Hora de salida (HH:MM): "; cin >> salida;
        cout << "Hora de llegada (HH:MM): "; cin >> llegada;
        cout << "Aerolínea: "; cin.ignore(); getline(cin, aerolinea);

        vuelo.set("codigo_vuelo", codigo);
        vuelo.set("id_origen", to_string(origen));
        vuelo.set("id_destino", to_string(destino));
        vuelo.set("fecha", fecha);
        vuelo.set("hora_abordaje", abordaje);
        vuelo.set("hora_salida", salida);
        vuelo.set("hora_llegada", llegada);
        vuelo.set("aerolinea", aerolinea);

        cout << (vuelo.create() ? "Vuelo creado exitosamente.\n" : "Error al crear vuelo.\n");
    }

    void leer() {
        auto lista = orm.getAll();
        for (auto& reg : lista) {
            cout << "ID: " << reg["id"] << ", Codigo: " << reg["codigo_vuelo"]
                 << ", Origen (ID): " << reg["id_origen"]
                 << ", Destino (ID): " << reg["id_destino"]
                 << ", Fecha: " << reg["fecha"]
                 << ", Abordaje: " << reg["hora_abordaje"]
                 << ", Salida: " << reg["hora_salida"]
                 << ", Llegada: " << reg["hora_llegada"]
                 << ", Aerolínea: " << reg["aerolinea"] << endl;
        }
        cout << "Presiona Enter para continuar..." << endl;
        cin.ignore(); cin.get();
    }

    void actualizar() {
        EloquentORM vuelo(conn, "vuelos", {"id", "codigo_vuelo", "id_origen", "id_destino", "fecha", "hora_abordaje", "hora_salida", "hora_llegada", "aerolinea"});
        int id, origen, destino;
        string codigo, fecha, abordaje, salida, llegada, aerolinea;

        cout << "ID del vuelo a actualizar: "; cin >> id;
        cout << "Nuevo codigo: "; cin >> codigo;
        cout << "ID nuevo aeropuerto origen: "; cin >> origen;
        cout << "ID nuevo aeropuerto destino: "; cin >> destino;
        cout << "Nueva fecha (YYYY-MM-DD): "; cin >> fecha;
        cout << "Hora de abordaje: "; cin >> abordaje;
        cout << "Hora de salida: "; cin >> salida;
        cout << "Hora de llegada: "; cin >> llegada;
        cout << "Nueva aerolínea: "; cin.ignore(); getline(cin, aerolinea);

        vuelo.set("id", to_string(id));
        vuelo.set("codigo_vuelo", codigo);
        vuelo.set("id_origen", to_string(origen));
        vuelo.set("id_destino", to_string(destino));
        vuelo.set("fecha", fecha);
        vuelo.set("hora_abordaje", abordaje);
        vuelo.set("hora_salida", salida);
        vuelo.set("hora_llegada", llegada);
        vuelo.set("aerolinea", aerolinea);

        cout << (vuelo.update() ? "Vuelo actualizado correctamente.\n" : "Error al actualizar vuelo.\n");
    }

    void eliminar() {
        EloquentORM vuelo(conn, "vuelos", {"codigo_vuelo"});
        int id;
        cout << "ID del vuelo a eliminar: "; cin >> id;

        if (vuelo.find(id)) {
            cout << "Se eliminó el vuelo: " << vuelo.get("codigo_vuelo") << endl;
            vuelo.remove();
        } else {
            cout << "No se encontró vuelo con ese ID.\n";
        }
    }
};

class Aeropuerto {
    MySQLConexion& conn;
    EloquentORM orm;
public:
    Aeropuerto(MySQLConexion& conexion)
        : conn(conexion), orm(conexion, "aeropuertos", {"codigo", "nombre"}) {}

    void crear() {
        EloquentORM aeropuerto(conn, "aeropuertos", {"codigo", "nombre"});
        string codigo, nombre;
        cout << "Codigo del aeropuerto (ej. GUA): "; cin >> codigo;
        cout << "Nombre del aeropuerto: "; cin.ignore(); getline(cin, nombre);

        aeropuerto.set("codigo", codigo);
        aeropuerto.set("nombre", nombre);

        cout << (aeropuerto.create() ? "Aeropuerto creado exitosamente.\n" : "Error al crear aeropuerto.\n");
    }

    void leer() {
        auto lista = orm.getAll();
        for (auto& reg : lista) {
            cout << "ID: " << reg["id"] << ", Codigo: " << reg["codigo"]
                 << ", Nombre: " << reg["nombre"] << endl;
        }
        cout << "Presiona Enter para continuar..." << endl;
        cin.ignore(); cin.get();
    }

    void actualizar() {
        EloquentORM aeropuerto(conn, "aeropuertos", {"id", "codigo", "nombre"});
        int id;
        cout << "ID del aeropuerto a actualizar: "; cin >> id;
        string codigo, nombre;
        cout << "Nuevo codigo: "; cin >> codigo;
        cout << "Nuevo nombre: "; cin.ignore(); getline(cin, nombre);

        aeropuerto.set("id", to_string(id));
        aeropuerto.set("codigo", codigo);
        aeropuerto.set("nombre", nombre);

        cout << (aeropuerto.update() ? "Aeropuerto actualizado.\n" : "Error al actualizar aeropuerto.\n");
    }

    void eliminar() {
        EloquentORM aeropuerto(conn, "aeropuertos", {"codigo", "nombre"});
        int id;
        cout << "ID del aeropuerto a eliminar: "; cin >> id;

        if (aeropuerto.find(id)) {
            cout << "Se elimino el aeropuerto: " << aeropuerto.get("nombre") << endl;
            aeropuerto.remove();
        } else {
            cout << "No se encontro aeropuerto con ese ID.\n";
        }
    }
};
class GeneradorHTML {
    MySQLConexion& conn;

public:
    GeneradorHTML(MySQLConexion& conexion) : conn(conexion) {}

    void generarPaseDeAbordar(int id_reserva) {
        MYSQL* mysql = conn.getConnection();

        stringstream query;
        query << "SELECT r.codigo_reserva, r.numero_boleto, r.asiento, "
              << "p.nombre, p.apellido, "
              << "v.codigo_vuelo, v.fecha, v.hora_abordaje, v.hora_salida, v.hora_llegada, v.aerolinea, "
              << "a1.codigo AS origen, a1.nombre AS origen_nombre, "
              << "a2.codigo AS destino, a2.nombre AS destino_nombre "
              << "FROM reservas r "
              << "JOIN pasajeros p ON r.id_pasajero = p.id "
              << "JOIN vuelos v ON r.id_vuelo = v.id "
              << "JOIN aeropuertos a1 ON v.id_origen = a1.id "
              << "JOIN aeropuertos a2 ON v.id_destino = a2.id "
              << "WHERE r.id = " << id_reserva;

        if (mysql_query(mysql, query.str().c_str()) != 0) {
            cerr << "❌ Error en la consulta: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* resultado = mysql_store_result(mysql);
        if (!resultado) {
            cerr << "❌ Error al obtener resultado: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(resultado);
        if (!row) {
            cout << "❌ No se encontró ninguna reserva con ese ID.\n";
            mysql_free_result(resultado);
            return;
        }

        string codigo_reserva = row[0];
        string numero_boleto = row[1];
        string asiento = row[2];
        string nombre = row[3];
        string apellido = row[4];
        string codigo_vuelo = row[5];
        string fecha = row[6];
        string hora_abordaje = row[7];
        string hora_salida = row[8];
        string hora_llegada = row[9];
        string aerolinea = row[10];
        string origen = row[11];
        string origen_nombre = row[12];
        string destino = row[13];
        string destino_nombre = row[14];

        mysql_free_result(resultado);

        ofstream html("pase_de_abordar.html");
        html << R"(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <title>Pase de abordar</title>
  <style>
    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      background-color: #f8f9fa;
      padding: 30px;
    }
    .ticket {
      width: 800px;
      margin: auto;
      border: 1px solid #ccc;
      background: #fff;
      padding: 20px 30px;
      box-shadow: 0 0 10px rgba(0,0,0,0.15);
      font-size: 15px;
      position: relative;
    }
    .header {
      display: flex;
      justify-content: space-between;
      align-items: flex-start;
    }
    .header-left {
      text-align: left;
    }
    .header-left h2 {
      color: #009fe3;
      margin: 0;
      font-weight: 800;
    }
    .header-left h3 {
      margin: 0;
      font-weight: 500;
    }
    .codes {
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin: 20px 0;
      font-size: 22px;
      font-weight: bold;
    }
    .codes div {
      text-align: center;
      flex: 1;
    }
    .codes span {
      font-size: 36px;
    }
    .flight-info {
      display: flex;
      justify-content: space-between;
      margin-top: 10px;
      font-size: 13px;
    }
    .flight-info div {
      flex: 1;
    }
    .info-table {
      width: 100%;
      border-collapse: collapse;
      margin-top: 20px;
    }
    .info-table th,
    .info-table td {
      padding: 10px;
      border-bottom: 1px solid #ccc;
      text-align: center;
    }
    .info-table th {
      font-size: 12px;
      color: #555;
    }
    .info-table td {
      font-size: 16px;
    }
    .info-table .seat {
      color: red;
      font-weight: bold;
    }
    .instructions {
      margin-top: 20px;
      font-size: 12px;
      text-align: center;
      line-height: 1.6;
    }
    .qr {
      position: absolute;
      top: 30px;
      right: 30px;
    }
    .qr img {
      height: 100px;
      width: 100px;
    }
  </style>
</head>
<body>
  <div class="ticket">
    <div class="header">
      <div class="header-left">
        <h2>PASE DE ABORDAR</h2>
        <h3>BOARDING PASS</h3>
        <p><strong>)" << nombre << " " << apellido << R"(</strong></p>
      </div>
      <div class="qr">
        <img src="https://api.qrserver.com/v1/create-qr-code/?data=)" << codigo_reserva << R"(&size=100x100" alt="QR">
      </div>
    </div>

    <div class="codes">
      <div>
        <div>)" << origen_nombre << R"(</div>
        <span>)" << origen << R"(</span>
      </div>
      <div>
        <img src="C:\Users\Rockstars\Desktop\Proyecto Progra\Captura de pantalla 2025-06-12 160738.png">
      </div>
      <div>
        <div>)" << destino_nombre << R"(</div>
        <span>)" << destino << R"(</span>
      </div>
    </div>

    <div class="flight-info">
      <div>
        <p>Fecha / date <strong>)" << fecha << R"(</strong></p>
        <p>Familia tarifaria / Fare family</p>
      </div>
      <div style="text-align: right;">
        <p>Código de reservación / Booking number <strong>)" << codigo_reserva << R"(</strong></p>
        <p>No. de boleto / Ticket # <strong>)" << numero_boleto << R"(</strong></p>
      </div>
    </div>

    <table class="info-table">
      <thead>
        <tr>
          <th>Hora de abordaje<br>Boarding time</th>
          <th>Salida<br>Departure</th>
          <th>Llegada<br>Arrival</th>
          <th>Vuelo<br>Flight</th>
          <th>Asiento<br>Seat</th>
          <th>Operado por<br>Operated by</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>)" << hora_abordaje << R"(</td>
          <td>)" << hora_salida << R"(</td>
          <td>)" << hora_llegada << R"(</td>
          <td>)" << codigo_vuelo << R"(</td>
          <td class="seat">)" << asiento << R"(</td>
          <td>)" << aerolinea << R"(</td>
        </tr>
      </tbody>
    </table>

    <div class="instructions">
      Preséntese en el aeropuerto 2 horas antes de la salida de su vuelo. Hora de abordaje 45 minutos antes de la salida del vuelo. La puerta cierra 15 minutos antes de la salida.<br>
      Show up at the airport 2 hours before departure of your flight. Boarding time 45 minutes before flight departure. Door closing 15 minutes before departure.
    </div>
  </div>
</body>
</html>
)";
        html.close();

        cout << "✅ Pase generado: pase_de_abordar.html\n";
        ShellExecute(NULL, "open", "pase_de_abordar.html", NULL, NULL, SW_SHOWNORMAL);
    }
};


void mostrar_menu_entidad(const string& nombreEntidad) {
    cout << "\n--- " << nombreEntidad << " ---\n";
    cout << "1. Crear\n";
    cout << "2. Leer\n";
    cout << "3. Actualizar\n";
    cout << "4. Eliminar\n";
    cout << "5. Volver al menu principal\n";
}

int main () {
    MySQLConexion conexion("root", "Julio05060709", "sistema_vuelos");
    if (!conexion.open()) {
        cerr << "No se pudo conectar a la base de datos." << endl;
        return 1;
    }
    Aeropuerto aeropuerto(conexion);
    Vuelo vuelo(conexion);
    Pasajero pasajero(conexion);
    Reserva reserva(conexion);
    UsuarioSistema usuario(conexion);
    GeneradorHTML generadorHTML(conexion);

        // Mostrar el menú principal
    cout << "Bienvenido al sistema de gestion de estudiantes.\n";
    int opcionEntidad = 0, opcionAccion = 0;

    do {
        cout << "\n==== MENU PRINCIPAL ====\n";
        cout << "1. Aereopuerto\n";
        cout << "2. Vuelos\n";
        cout << "3. Pasajeros\n";
        cout << "4. Reservas\n";
        cout << "5. Usuario del sistema\n"; 
        cout << "6. Generar pase de abordar\n";   
        cout << "7. Salir\n";  
        cout << "=========================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionEntidad;

        // Validar la entrada
        if (cin.fail() || opcionEntidad < 1 || opcionEntidad > 7) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar la entrada incorrecta
            cout << "Opción no válida. Intente de nuevo.\n";
            continue; // Volver al menú principal
        }

        if (opcionEntidad == 7) {
            cout << "Saliendo del sistema...\n";
            break; // Salir del programa
        }

        mostrar_menu_entidad(
            opcionEntidad == 1 ? "Aereopuertos" :
            opcionEntidad == 2 ? "Vuelos" :
            opcionEntidad == 3 ? "Pasajeros" : 
            opcionEntidad == 4 ? "Reservas" : "Usuario del sistema"
        );
        if (opcionEntidad == 6) {
            cout << "Generar pase de abordar\n";
            cout << "Ingrese el ID de la reserva para generar el pase de abordar: ";
            int id_reserva;
            cin >> id_reserva;
            generadorHTML.generarPaseDeAbordar(id_reserva);
            continue; // Volver al menú principal
        }

        cin >> opcionAccion;

        if (opcionAccion < 1 || opcionAccion > 5) {
            cout << "Opción no válida. Intente de nuevo.\n";
            continue; // Volver al menú principal
        }

        switch (opcionEntidad) {
            case 1: // Aereopuertos
                switch (opcionAccion) {
                    case 1: aeropuerto.crear(); break;
                    case 2: aeropuerto.leer(); break;
                    case 3: aeropuerto.actualizar(); break;
                    case 4: aeropuerto.eliminar(); break;
                    case 5: continue; // Volver al menú principal
                    default: cout << "Opción no válida.\n"; break;
                }
                break;
            case 2: // Vuelos
                switch (opcionAccion) {
                    case 1: vuelo.crear(); break;
                    case 2: vuelo.leer(); break;
                    case 3: vuelo.actualizar(); break;
                    case 4: vuelo.eliminar(); break;
                    case 5: continue; // Volver al menú principal
                    default: cout << "Opción no válida.\n"; break;
                }
                break;
            case 3: // Pasajeros
                switch (opcionAccion) {
                    case 1: pasajero.crear(); break;
                    case 2: pasajero.leer(); break;
                    case 3: pasajero.actualizar(); break;
                    case 4: pasajero.eliminar(); break;
                    case 5: continue; // Volver al menú principal
                    default: cout << "Opción no válida.\n"; break;
                }
                break;
            case 4: // Reservas
                switch (opcionAccion) {
                    case 1: reserva.crear(); break;
                    case 2: reserva.leer(); break;
                    case 3: reserva.actualizar(); break;
                    case 4: reserva.eliminar(); break;
                    case 5: continue; // Volver al menú principal
                    default: cout << "Opción no válida.\n"; break;
                }
                break;
            case 5: // Usuario del sistema
                switch (opcionAccion) {
                    case 1: usuario.crear(); break;
                    case 2: usuario.leer(); break;
                    case 3: usuario.actualizar(); break;
                    case 4: usuario.eliminar(); break;
                    case 5: continue; // Volver al menú principal
                    default: cout << "Opción no válida.\n"; break;
                }
                break;
            default:
                cout << "Opción no válida.\n";
                break;
        }

    } while (true);
    
    // Cerrar la conexión a la base de datos
    conexion.close();
    cout << "Conexion cerrada. Saliendo del sistema...\n";
    return 0;
}
