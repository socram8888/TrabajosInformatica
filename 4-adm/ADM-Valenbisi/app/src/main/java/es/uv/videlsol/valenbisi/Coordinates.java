package es.uv.videlsol.valenbisi;

import android.net.Uri;

import org.json.JSONArray;
import org.json.JSONException;

import java.io.Serializable;

/**
 * Created by Marcos on 21/03/2017.
 */

public final class Coordinates implements Serializable {
    public final double latitude;
    public final double longitude;
    private static final long serialVersionUID = 1L;

    public Coordinates(JSONArray arr) throws JSONException {
        latitude = arr.getDouble(1);
        longitude = arr.getDouble(0);
    }

    public Coordinates(double latitude, double longitude) {
        this.latitude = latitude;
        this.longitude = longitude;
    }

    @Override
    public String toString() {
        return latitude + "," + longitude;
    }

    public Uri toUri() {
        return Uri.parse("geo:0,0?q=" + latitude + "," + longitude);
    }

    public Uri toUri(String desc) {
        return Uri.parse("geo:0,0?q=" + latitude + "," + longitude + "(" + desc + ")");
    }
}
