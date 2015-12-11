package universidad.model;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Random;
import lombok.SneakyThrows;

public class Universidad {

    private ArrayList<UsuarioRegistrado> usuarios = new ArrayList<UsuarioRegistrado>();
    private ArrayList<Titulacion> titulaciones = new ArrayList<Titulacion>();
    private GestorUniversidad gestorUniversidad;
    private byte[] passSalt;

    public UsuarioRegistrado iniciarSesion(String usuario, String pass) {
        byte[] passHash = calcularPassHash(usuario, pass);

        for (UsuarioRegistrado usuarioRegistrado : usuarios) {
            if (usuarioRegistrado.comprobarInicioSesion(usuario, passHash)) {
                return usuarioRegistrado;
            }
        }

        return null;
    }

    @SneakyThrows({NoSuchAlgorithmException.class, UnsupportedEncodingException.class})
    public byte[] calcularPassHash(String usuario, String pass) {
        MessageDigest md = MessageDigest.getInstance("SHA-256");

        byte[] bytesPass = pass.getBytes("UTF-8");
        md.update(bytesPass);

        byte[] bytesUsuario = usuario.getBytes("UTF-8");
        md.update(bytesUsuario);

        md.update(passSalt);
        return md.digest();
    }

    public void setGestorUniversidad(GestorUniversidad gestorUniversidad) {
        this.gestorUniversidad = gestorUniversidad;
    }

    public void cargarDatos() {
        Calendar clndr = Calendar.getInstance();
        Date apertura, cierre;

        Random rnd = new Random();
        passSalt = new byte[16];
        rnd.nextBytes(passSalt);

        Profesor maria = crearProfesor("María", "Fontaneda Chang", "mfonchan", "mfonchan-pass");
        Profesor arturo = crearProfesor("Arturo", "Pérez Machado", "arperez", "arperez-pass");
        Profesor paco = crearProfesor("Francisco", "Pérez Churchill", "arperchu", "arperchu-pass");

        clndr.set(2015, 2, 15);
        apertura = clndr.getTime();
        clndr.set(2015, 9, 16);
        cierre = clndr.getTime();
        Titulacion informatica = crearTitulacion("Informática", apertura, cierre);

        Teoria isi = informatica.crearTeoria("Ingeniería del software");
        isi.crearSubgrupo(60, maria);

        Laboratorio isiLab = informatica.crearLaboratorio(isi);
        isiLab.crearSubgrupo(5, maria);
        isiLab.crearSubgrupo(5, arturo);

        Teoria bbdd = informatica.crearTeoria("Bases de datos");
        bbdd.crearSubgrupo(60, paco);
        Laboratorio bbddLab = informatica.crearLaboratorio(bbdd);
        bbddLab.crearSubgrupo(20, paco);
        bbddLab.crearSubgrupo(8, paco);
        
        clndr.set(2015, 3, 23);
        apertura = clndr.getTime();
        clndr.set(2015, 3, 28);
        cierre = clndr.getTime();
        Titulacion magisterio = crearTitulacion("Magisterio", apertura, cierre);
        
        Teoria pinta = magisterio.crearTeoria("Teoremas de lápices de colores");
        pinta.crearSubgrupo(80, maria);

        Teoria colores = magisterio.crearTeoria("Sumas y restas");
        colores.crearSubgrupo(80, maria);
        
        Teoria vela1 = magisterio.crearTeoria("Observación de vela encendida I");
        vela1.crearSubgrupo(80, maria);
        
        Teoria vela2 = magisterio.crearTeoria("Observación de vela encendida II");
        vela2.crearSubgrupo(80, maria);

        crearAlumno("Pedro", "De Los Palotes", "palope", "palope-pass", informatica);
        crearAlumno("Ana", "Maria Antúnez", "anamatuz", "anamatuz-pass", informatica);
        crearAlumno("Luis Javier", "Martínez Guimerá", "jluismar", "jluismar-pass", informatica);
        crearAlumno("Arturo", "Olivares", "arolivar", "arolivar-pass", informatica);
        crearAlumno("Beatriz", "Monzo Bernat", "beamonzo", "beamonzo-pass", informatica);
        crearAlumno("Marcos", "Vives Del Sol", "videlsol", "videlsol-pass", informatica);
        crearAlumno("Jorge", "Gimenez", "jogimene", "jogimene-pass", informatica);
        crearAlumno("Pablo", "Motos Burgos", "pmotosb", "pmotosb-pass", informatica);
        crearAlumno("Santiago", "Segura Silva", "ssegursil", "ssegursil-pass", informatica);

        crearAlumno("Jose", "Ramón Ramírez", "jramon", "jramon-pass", magisterio);
        crearAlumno("Pedro", "Picapiedra", "pedpica", "pedpica-pass", magisterio);
    }

    public Titulacion crearTitulacion(String nombre, Date apertura, Date cierre) {
        Titulacion titulacion = new Titulacion(this, nombre, titulaciones.size() + 1, apertura, cierre);
        titulaciones.add(titulacion);
        return titulacion;
    }
    
    public Alumno crearAlumno(String nombre, String apellidos, String usuario, String pass, Titulacion titulacion) {
        byte[] passHash = calcularPassHash(usuario, pass);
        Alumno alumno = new Alumno(this, nombre, apellidos, usuario, passHash, titulacion);
        usuarios.add(alumno);
        return alumno;
    }
    
    public Profesor crearProfesor(String nombre, String apellidos, String usuario, String pass) {
        byte[] passHash = calcularPassHash(usuario, pass);
        Profesor profesor = new Profesor(this, nombre, apellidos, usuario, passHash);
        usuarios.add(profesor);
        return profesor;
    }
    
    public void realizarBackup() {
        gestorUniversidad.realizarBackup();
    }
    
    public ArrayList<Titulacion> getTitulaciones(){
        return titulaciones;
    }
}
