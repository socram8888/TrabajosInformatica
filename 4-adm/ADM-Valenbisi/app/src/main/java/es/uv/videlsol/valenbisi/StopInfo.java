package es.uv.videlsol.valenbisi;

import android.net.Uri;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.Serializable;

/**
 * Created by alumno on 21/02/2017.
 */

public class StopInfo implements Serializable {
    private static final long serialVersionUID = 1;

    public static final long NEVER_UPDATED = -1;

    private int number;
    private String name;
    private String address;

    private long lastUpdate = NEVER_UPDATED;
    private int usedSlots;
    private int freeSlots;
    private int totalSlots;

    private Coordinates coordinates;

    public StopInfo(JSONObject feat) throws JSONException {
        if (!"Feature".equals(feat.getString("type"))) {
            throw new JSONException("Type is not \"Feature\"");
        }

        JSONObject props = feat.getJSONObject("properties");
        number = props.getInt("number");
        name = props.getString("name");
        address = props.getString("address");

        if (props.getString("updated_at").length() > 0) {
            lastUpdate = props.getLong("updated_at");
            usedSlots = props.getInt("available");
            freeSlots = props.getInt("free");
            totalSlots = props.getInt("total");
        }

        JSONObject geom = feat.getJSONObject("geometry");
        if (!"Point".equals(geom.getString("type"))) {
            throw new JSONException("Coordinate object has an invalid type");
        }

        coordinates = new Coordinates(geom.getJSONArray("coordinates"));
    }

    public int getNumber() {
        return number;
    }

    public String getName() {
        return name;
    }

    public String getAddress() {
        return address;
    }

    public boolean hasSlotInfo() {
        return lastUpdate != NEVER_UPDATED;
    }

    public long getLastUpdate() {
        return lastUpdate;
    }

    public int getUsedSlots() {
        return usedSlots;
    }

    public int getFreeSlots() {
        return freeSlots;
    }

    public int getTotalSlots() {
        return totalSlots;
    }

    public Coordinates getCoordinates() {
        return coordinates;
    }

    public Uri getCoordinatesUri() {
        return coordinates.toUri(name);
    }
}
