package es.uv.videlsol.valenbisi;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * Created by alumno on 21/02/2017.
 */

public class StopDatabase implements Serializable {
    private static final long serialVersionUID = 1;

    private final List<StopInfo> stops;
    private final List<StopInfo> immutableStops;

    public StopDatabase(String str) throws JSONException {
        this(new JSONObject(str));
    }

    public StopDatabase(JSONObject json) throws JSONException {
        if (!"FeatureCollection".equals(json.getString("type"))) {
            throw new JSONException("Not a collection (- cannot parse stop database");
        }

        JSONArray feats = json.getJSONArray("features");
        stops = new ArrayList<>(feats.length());

        for (int i = 0; i < feats.length(); i++) {
            stops.add(new StopInfo(feats.getJSONObject(i)));
        }

        immutableStops = Collections.unmodifiableList(stops);
    }

    public List<StopInfo> list() {
        return immutableStops;
    }

    public StopDatabase sortByAddress() {
        Collections.sort(stops, ADDRESS_SORTER);
        return this;
    }

    private static final Comparator<StopInfo> ADDRESS_SORTER = new Comparator<StopInfo>() {
        @Override
        public int compare(StopInfo o1, StopInfo o2) {
            return o1.getAddress().compareToIgnoreCase(o2.getAddress());
        }
    };
}

