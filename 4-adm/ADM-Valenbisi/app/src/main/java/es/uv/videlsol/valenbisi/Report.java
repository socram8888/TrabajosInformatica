package es.uv.videlsol.valenbisi;

import android.content.ContentValues;
import android.support.annotation.NonNull;

import java.io.Serializable;

/**
 * Created by Marcos on 28/03/2017.
 */

public class Report implements Serializable {
    private static final long serialVersionUID = 1;

    private final int stopId;
    private long id = -1;
    @NonNull private String subject = "";
    @NonNull private String description = "";
    @NonNull private Report.Type type = Type.MECHANIC;
    @NonNull private Report.Status status = Status.OPEN;

    public Report(@NonNull StopInfo stop) {
        this.stopId = stop.getNumber();
    }

    public Report(int stopId) {
        this.stopId = stopId;
    }

    @NonNull
    public int getStopId() {
        return stopId;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @NonNull
    public String getSubject() {
        return subject;
    }

    public void setSubject(@NonNull String subject) {
        this.subject = subject;
    }

    @NonNull
    public String getDescription() {
        return description;
    }

    public void setDescription(@NonNull String description) {
        this.description = description;
    }

    @NonNull
    public Type getType() {
        return type;
    }

    public void setType(@NonNull Type type) {
        this.type = type;
    }

    @NonNull
    public Status getStatus() {
        return status;
    }

    public void setStatus(@NonNull Status status) {
        this.status = status;
    }

    public enum Type {
        MECHANIC, ELECTRIC, PAINTING, BUILDING;
    }

    public enum Status {
        OPEN, PROCESSING, CLOSED;
    }
}
